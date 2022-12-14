#include "GameScene.h"
#include "YMath.h"
#include "CalcTransform.h"
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

#pragma region �ǂݍ���
void GameScene::Load()
{
	// ----- �e�N�X�`�� ----- //

	plainT_ = pTexManager_->Load("white1x1.png", false);

	playerT_ = pTexManager_->Load("player.png", true);
	enemyT_ = pTexManager_->Load("enemy.png", true);

	mapDispT_ = pTexManager_->Load("mapDisp.png", false);

	// ----- �I�[�f�B�I ----- //

	aA_ = pAudioManager_->Load("Resources/Audios/fanfare.wav");

	// ----- ���f�� ----- //

	cubeM_.reset(Model::Create());
	skydomeM_.reset(Model::Load("skydome"));
	//skydomeM_.reset(Model::Load({ "skydome/", "skydome.obj", false, false, true }));
	//skydomeM_.reset(Model::Load({ "skydome/", "skydome.obj", false, false, true }));

	aliciaM_.reset(Model::Load({ "Alicia/FBX/", "Alicia_solid_Unity.FBX", false, true, false, "tga" }));
	zundamonM_.reset(Model::Load({ "zundamon/", "zundamon.pmx", false, true, false }));

	// ----- �X�v���C�g ----- //

	curtenS_.reset(Sprite::Create({ WinSize }, { plainT_ }));
	//mapDispS_.reset(Sprite::Create({ {32,32} }, { mapDispT_ }));

	// ----- �}�b�v ----- //

	//map_.Load({ "stage1.csv", cubeM_.get(), mapDispT_, mapDispS_.get()});

	// ----- �ÓI������ ----- //

	Transition::Blackout::StaticInitialize({ curtenS_.get() });
	Player::StaticIntialize({ cubeM_.get(), playerT_ });

}
#pragma endregion


#pragma region ������
void GameScene::Initialize()
{
	// ����������
	Srand();

	// ��������
	const size_t s = 8;
	for (size_t i = 0; i < s; i++)
	{
		std::vector<Object> fs;
		for (size_t j = 0; j < s; j++)
		{
			Object f;
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
			f.Update();
			fs.push_back(f);
		}
		floor.push_back(fs);
	}

	sprite_.Initialize({ });

	// �v���C���[������
	player_ = std::make_unique<Player>();
	player_->Initialize();

	// �G�l�~�[������
	//enemy_.Initialize({ {0,5.0f,20.0f},{},{5.0f,5.0f,5.0f} });
	//enemy_.rota_ = AdjustAngle(Vec3(0, 0, -1));

	alicia_.Initialize({ {-45.0f,0.0f,+100.0f} });
	alicia_.rota_ = AdjustAngle(Vec3(0, 0, -1));
	
	zundamon_.Initialize({ {+45.0f,0.0f,+100.0f}, {}, {10,10,10} });
	zundamon_.rota_ = AdjustAngle(Vec3(0, 0, -1));

	// �}�b�v������
	//map_.Initialize({ 7.5f, {}});
	//map_.Initialize({ 7.5f, { 0.0f,+30.0f,-25.0f }});

	// �V��������
	skydome_.Initialize(skydomeM_.get());

	// �J����������
	//camera_.Initialize({ {150.0f, 50.0f, -50.0f}, {PI / 16.0f, -PI / 3.0f, 0.0f} });
	//camera_.Initialize({ {200.0f, -20.0f, 115.0f}, {0.0f, -PI / 2.0f, 0.0f} });
	camera_.Initialize({ {0.0f,100.0f,-200.0f} });

	// �r���[�v���W�F�N�V����������
	vp_.Initialize({});

	sceneMan_.Initialize();
	collMan_.Initialize();
}
#pragma endregion


#pragma region �X�V
void GameScene::Update()
{
	// �z�b�g�����[�h
	if (keys_->IsTrigger(DIK_L))
	{
		//map_.Load({ "stage1.csv", cubeM_.get(), mapDispT_, mapDispS_.get() });
		//map_.Reset({ 0.0f,+30.0f,-25.0f });
	}

	// ���Z�b�g
	if (keys_->IsTrigger(DIK_R))
	{
		// �v���C���[
		player_->Reset();
		// �G�l�~�[
		enemy_.rota_  = AdjustAngle(Vec3(0, 0, -1));

		collMan_.Initialize();
	}

	if (sceneMan_.GetScene() == Scene::TITLE)
	{

	}
	else if (sceneMan_.GetScene() == Scene::TUTORIAL)
	{

	}
	else if (sceneMan_.GetScene() == Scene::PLAY)
	{

	}
	else if (sceneMan_.GetScene() == Scene::PAUSE) 
	{

	}
	else if (sceneMan_.GetScene() == Scene::CLEAR) 
	{

	}
	else if (sceneMan_.GetScene() == Scene::OVER) 
	{

	}
	
	// �v���C���[
	if (keys_->IsTrigger(DIK_SPACE)) { player_->Jump(); }
	if (keys_->IsTrigger(DIK_RETURN)) { player_->Attack(); }

	//player_->SpeedRef().z_ = keys_->Horizontal(Keys::MoveStandard::WASD) * 3.0f;
	//player_->SpeedRef().y_ = -keys_->Vertical(Keys::MoveStandard::WASD) * 3.0f;

	player_->Update();

	// �G�l�~�[
	//enemy_.pos_.z_ += +keys_->Horizontal(Keys::MoveStandard::Arrow) * 0.2f;
	//enemy_.pos_.y_ += -keys_->Vertical(Keys::MoveStandard::Arrow) * 0.2f;

	enemy_.Update();

	// �}�b�v�}�l�[�W���[
	//map_.Update();
	//map_.PerfectPixelCollision(*player_.get());

	// �X�J�C�h�[��
	skydome_.Update();

	player_->UpdateMove();
	player_->UpdateMatrix();

	alicia_.pos_.x_ += +keys_->Horizontal(Keys::MoveStandard::WASD) * 3.0f;
	alicia_.pos_.z_ += -keys_->Vertical(Keys::MoveStandard::WASD) * 3.0f;
	alicia_.Update();

	zundamon_.pos_.x_ += +keys_->Horizontal(Keys::MoveStandard::Arrow) * 3.0f;
	zundamon_.pos_.z_ += -keys_->Vertical(Keys::MoveStandard::Arrow) * 3.0f;
	zundamon_.Update();


	// �J����
	//camera_.pos_.x_ += +keys_->Horizontal(Keys::MoveStandard::WASD) * 3.0f;
	//camera_.pos_.z_ += -keys_->Vertical(Keys::MoveStandard::WASD) * 3.0f;
	//camera_.rota_.y_ += +keys_->Horizontal(Keys::MoveStandard::Arrow) * 0.02f;
	//camera_.rota_.x_ += -keys_->Vertical(Keys::MoveStandard::Arrow) * 0.02f;
	camera_.Update();

	// �r���[�v���W�F�N�V����
	vp_ = camera_.GetViewProjection();
	vp_.Update();

	// �V�[���}�l�[�W���[
	if (keys_->IsTrigger(DIK_1)){ sceneMan_.Change(Scene::PLAY); }
	sceneMan_.Update();
}
#pragma endregion


#pragma region �`��
void GameScene::DrawBackSprites()
{
	if (sceneMan_.GetScene() == Scene::TITLE)
	{

	}
	else if (sceneMan_.GetScene() == Scene::TUTORIAL)
	{

	}
	else if (sceneMan_.GetScene() == Scene::PLAY)
	{

	}
	else if (sceneMan_.GetScene() == Scene::PAUSE)
	{

	}
	else if (sceneMan_.GetScene() == Scene::CLEAR)
	{

	}
	else if (sceneMan_.GetScene() == Scene::OVER)
	{

	}

}

void GameScene::DrawModels()
{
	if (sceneMan_.GetScene() == Scene::TITLE)
	{

	}
	else if (sceneMan_.GetScene() == Scene::TUTORIAL)
	{

	}
	else if (sceneMan_.GetScene() == Scene::PLAY)
	{

	}
	else if (sceneMan_.GetScene() == Scene::PAUSE)
	{

	}
	else if (sceneMan_.GetScene() == Scene::CLEAR)
	{

	}
	else if (sceneMan_.GetScene() == Scene::OVER)
	{

	}

	skydome_.Draw(vp_);


	// floor
	for (size_t i = 0; i < floor.size(); i++)
	{
		for (size_t j = 0; j < floor[i].size(); j++)
		{
			cubeM_->Draw(floor[i][j], vp_);
		}
	}

	aliciaM_->Draw(alicia_, vp_);
	zundamonM_->Draw(zundamon_, vp_);

	// player
	//player_->Draw(vp_);
	// enemy
	//cubeM_->Draw(enemy_, vp_, enemyT_);
	// map
	//map_.Draw(vp_);
}

void GameScene::DrawFrontSprites()
{
	if (sceneMan_.GetScene() == Scene::TITLE)
	{

	}
	else if (sceneMan_.GetScene() == Scene::TUTORIAL)
	{

	}
	else if (sceneMan_.GetScene() == Scene::PLAY)
	{

	}
	else if (sceneMan_.GetScene() == Scene::PAUSE)
	{

	}
	else if (sceneMan_.GetScene() == Scene::CLEAR)
	{

	}
	else if (sceneMan_.GetScene() == Scene::OVER)
	{

	}

	//map_.Draw2D();

	sceneMan_.Draw();
}

void GameScene::Draw()
{
	// -------------------------- //
	Sprite::StaticSetDrawCommand();
	// ----- �w�i�X�v���C�g ----- //

	DrawBackSprites();

	// -------------------------- //
	Model::StaticSetDrawCommand();
	// --------- ���f�� --------- //

	DrawModels();

	// -------------------------- //
	Sprite::StaticSetDrawCommand();
	// ----- �O�i�X�v���C�g ----- //

	DrawFrontSprites();
	
	// -------------------------- //
}
#pragma endregion