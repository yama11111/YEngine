#include "GameScene.h"
#include "Calc.h"
#include "Def.h"
#include <cassert>

#pragma region 名前空間宣言

using namespace DX;
using namespace Input;
using namespace Math;
using namespace Game;

#pragma endregion 

#pragma region Static関連

Keys* GameScene::keys_ = nullptr;
Mouse* GameScene::mouse_ = nullptr;
Pad* GameScene::pad_ = nullptr;
TextureManager* GameScene::pTexManager_ = nullptr;
AudioManager* GameScene::pAudioManager_ = nullptr;

void GameScene::StaticInitialize(TextureManager* pTexManager, AudioManager* pAudioManager)
{
	assert(pTexManager);
	assert(pAudioManager);
	pTexManager_ = pTexManager;
	pAudioManager_ = pAudioManager;

	keys_ = Keys::GetInstance();
	mouse_ = Mouse::GetInstance();
	pad_ = Pad::GetInstance();
}

#pragma endregion 

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize()
{
	plainT_ = pTexManager_->Load(L"Resources/Textures/white1x1.png", false);
	//plainT_ = pTexManager_->Load(L"Resources/Textures/player.png", false);
	
	aA_ = pAudioManager_->Load("Resources/Audios/fanfare.wav");

	cubeM_.reset(Model::Create());
	//cubeM_.reset(Model::Load("Resources/Models/triangleTex.obj"));

	quadS_.reset(new Sprite({ 64,64 }));

	const size_t s = 8;
	for (size_t i = 0; i < s; i++)
	{
		std::vector<Transform> fs;
		for (size_t j = 0; j < s; j++)
		{
			Transform f;
			f.Initialize({});
			f.scale_ = { 20,1,20 };
			f.pos_ =
			{
				((f.scale_.x_ * 2.0f) * j) - ((s - 1) * (f.scale_.x_)),
				-f.scale_.y_,
				((f.scale_.z_ * 2.0f) * i) - ((s - 1) * (f.scale_.z_))
			};
			float c = 1.0f - (((i + j) % 2 == 0) * 0.5f);
			f.SetColor({ c,c,c,1.0f });
			fs.push_back(f);
		}
		floor.push_back(fs);
	}

	PlayerDrawer::StaticInitialize(cubeM_.get(), plainT_);
	EnemyDrawer::StaticInitialize(cubeM_.get(), plainT_);

	player_.Initialize({ {0,0,-10} });
	player_.rota_ = AdjustAngle(Vec3(0, 0, 1));

	enemy_.Initialize({ {0,0,10} });
	enemy_.rota_ = AdjustAngle(Vec3(0, 0, -1));

	pd_.Initialize(&player_.m_);
	ed_.Initialize(&enemy_.m_);

	vp_.Initialize({});
	//vp_.eye_ = { 0,2.5,-10 };
	vp_.eye_ = { 0,5,-20 };
}

void GameScene::Update()
{
	if (keys_->IsTrigger(DIK_R))
	{
		player_.rota_ = AdjustAngle(Vec3(0,0,1));
		enemy_.rota_ = AdjustAngle(Vec3(0,0,-1));
		pd_.Reset(); 
		ed_.Reset();
	}

	//player_.rota_.x_ += -keys_->Vertical() * PI / 180;
	//player_.rota_.y_ += keys_->Horizontal() * PI / 180;

	player_.pos_.x_ += keys_->Horizontal() * 0.2f;
	player_.pos_.z_ += -keys_->Vertical() * 0.2f;

	if (keys_->IsMove())
	{
		Vec3 vel = Vec3(keys_->Horizontal(), 0, -keys_->Vertical()).Normalized();
		player_.rota_ = AdjustAngle(vel);
	}
	pd_.SetWalkActivate(keys_->IsMove());

	if (keys_->IsDown(DIK_J)) { pd_.SetWalkActivate(true); }

	player_.Update();
	pd_.Update();
	
	//enemy_.rota_.x_ += -pad_->Vertical(PadStick::LStick) * PI / 180;
	//enemy_.rota_.y_ += pad_->Horizontal(PadStick::LStick) * PI / 180;
	
	enemy_.pos_.x_ += pad_->Horizontal(PadStick::LStick) * 0.2f;
	enemy_.pos_.z_ += -pad_->Vertical(PadStick::LStick) * 0.2f;

	if (pad_->IsMove(PadStick::LStick))
	{
		Vec3 vel = Vec3(pad_->Horizontal(PadStick::LStick), 0, -pad_->Vertical(PadStick::LStick)).Normalized();
		enemy_.rota_ = AdjustAngle(vel);
	}
	ed_.SetWalkActivate(pad_->IsMove(PadStick::LStick));

	if (pad_->IsDown(PadInputNumber::XIP_X)) { ed_.SetWalkActivate(true); }

	enemy_.Update();
	ed_.Update();

	for (size_t i = 0; i < floor.size(); i++)
	{
		for (size_t j = 0; j < floor[i].size(); j++)
		{
			floor[i][j].Update();
		}
	}

	vp_.Update();

	if (keys_->IsTrigger(DIK_SPACE))
	{
		pAudioManager_->Play(aA_);
	}
}

void GameScene::Draw()
{
	// -------------------------- //
	Sprite::StaticSetDrawCommand();
	// ----- 背景スプライト ----- //



	// -------------------------- //
	Model::StaticSetDrawCommand();
	// --------- モデル --------- //

	for (size_t i = 0; i < floor.size(); i++)
	{
		for (size_t j = 0; j < floor[i].size(); j++)
		{
			cubeM_->Draw(floor[i][j], vp_, plainT_);
		}
	}

	//cubeM_->Draw(player_, vp_, plainT_);
	pd_.Draw(vp_);
	ed_.Draw(vp_);

	// -------------------------- //
	Sprite::StaticSetDrawCommand();
	// ----- 前景スプライト ----- //


	
	// -------------------------- //
}
