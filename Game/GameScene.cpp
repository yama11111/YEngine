#include "GameScene.h"
#include "Calc.h"
#include "Def.h"
#include <cassert>

#pragma region ���O��Ԑ錾

using namespace DX;
using namespace Input;
using namespace Math;
using namespace Game;

#pragma endregion 

#pragma region Static�֘A

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

	playerT_ = pTexManager_->Load(L"Resources/Textures/player.png", false);
	enemyT_ = pTexManager_->Load(L"Resources/Textures/enemy.png", false);
	
	//aA_ = pAudioManager_->Load("Resources/Audios/fanfare.wav");

	cubeM_.reset(Model::Create());
	//loadM_.reset(Model::Load("Resources/Models/triangleTex.obj"));
	loadM_.reset(Model::Load("triangleMat"));

	quadS_.reset(new Sprite({ 64,64 }));

	// ���f���ƃe�N�X�`���}��
	PlayerDrawer::StaticInitialize(cubeM_.get(), plainT_);
	EnemyDrawer::StaticInitialize(cubeM_.get(), plainT_);

	// ��������
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
			f.color_= { c,c,c,1.0f };
			fs.push_back(f);
		}
		floor.push_back(fs);
	}

	sprite_.Initialize({ });
	model_.Initialize({ {2,2,0} });

	// �v���C���[������
	player_.Initialize({ {0,1.0f,-10} });
	player_.rota_ = AdjustAngle(Vec3(0, 0, 1));

	// �G�l�~�[������
	enemy_.Initialize({ {0,1.0f,10} });
	enemy_.rota_ = AdjustAngle(Vec3(0, 0, -1));

	// �r���[�v���W�F�N�V����������
	vp_.Initialize({});
	vp_.eye_ = { 0,5,-20 };
}

void GameScene::Update()
{
	// ���Z�b�g
	if (keys_->IsTrigger(DIK_R))
	{
		// �v���C���[
		player_.rota_ = AdjustAngle(Vec3(0,0,1));
		// �G�l�~�[
		enemy_.rota_ = AdjustAngle(Vec3(0,0,-1));
	}

	// ----- Player ----- //
	// �v���C���[�ړ�
	player_.pos_.x_ += keys_->Horizontal(Keys::MoveStandard::WASD) * 0.2f;
	player_.pos_.z_ += -keys_->Vertical(Keys::MoveStandard::WASD) * 0.2f;

	// �v���C���[�ړ�������
	if (keys_->IsMove(Keys::MoveStandard::WASD))
	{
		// �p�x����
		Vec3 vel = Vec3(
			static_cast<float>(keys_->Horizontal(Keys::MoveStandard::WASD)),
			0,
			static_cast<float>(-keys_->Vertical(Keys::MoveStandard::WASD))).Normalized();
		player_.rota_ = AdjustAngle(vel);
	}

	// �A�b�v�f�[�g
	player_.Update();
	
	// ----- Enemy ----- //
	// �G�l�~�[�ړ�
	enemy_.pos_.x_ += keys_->Horizontal(Keys::MoveStandard::Arrow) * 0.2f;
	enemy_.pos_.z_ += -keys_->Vertical(Keys::MoveStandard::Arrow) * 0.2f;

	// �G�l�~�[�ړ�������
	if (keys_->IsMove(Keys::MoveStandard::Arrow))
	{
		Vec3 vel = Vec3(
			static_cast<float>(keys_->Horizontal(Keys::MoveStandard::Arrow)),
			0,
			static_cast<float>(-keys_->Vertical(Keys::MoveStandard::Arrow))).Normalized();
		enemy_.rota_ = AdjustAngle(vel);
	}

	// �A�b�v�f�[�g
	enemy_.Update();

	// ----- floor ----- //
	for (size_t i = 0; i < floor.size(); i++)
	{
		for (size_t j = 0; j < floor[i].size(); j++)
		{
			floor[i][j].Update();
		}
	}

	vp_.Update();

	//if (keys_->IsTrigger(DIK_SPACE))
	//{
	//	pAudioManager_->Play(aA_);
	//}
}

void GameScene::Draw()
{
	// -------------------------- //
	Sprite::StaticSetDrawCommand();
	// ----- �w�i�X�v���C�g ----- //

	quadS_->Draw(sprite_, plainT_);

	// -------------------------- //
	Model::StaticSetDrawCommand();
	// --------- ���f�� --------- //

	// floor
	for (size_t i = 0; i < floor.size(); i++)
	{
		for (size_t j = 0; j < floor[i].size(); j++)
		{
			cubeM_->Draw(floor[i][j], vp_, plainT_);
		}
	}

	loadM_->Draw(model_, vp_, playerT_);
	
	// player
	cubeM_->Draw(player_, vp_, playerT_);
	// enemy
	cubeM_->Draw(enemy_, vp_, enemyT_);

	// -------------------------- //
	Sprite::StaticSetDrawCommand();
	// ----- �O�i�X�v���C�g ----- //


	
	// -------------------------- //
}
