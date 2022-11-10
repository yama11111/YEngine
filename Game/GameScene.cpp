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
	aA_ = pAudioManager_->Load("Resources/Audios/fanfare.wav");

	cubeM_.reset(new Model());
	quadS_.reset(new Sprite({ 64,64 }));

	t1.Initialize({});
	t2.Initialize({});
	t3.Initialize({});

	vp_.Initialize({});
}

void GameScene::Update()
{
	t1.Update();
	t2.Update();
	t3.Update();

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

	quadS_->Draw(t1, plainT_);

	// -------------------------- //
	Model::StaticSetDrawCommand();
	// --------- モデル --------- //

	cubeM_->Draw(t2, vp_, plainT_);

	// -------------------------- //
	Sprite::StaticSetDrawCommand();
	// ----- 前景スプライト ----- //

	quadS_->Draw(t3, plainT_);
	
	// -------------------------- //
}
