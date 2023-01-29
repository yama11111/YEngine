#include "GameScene.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>

#pragma region ���O��Ԑ錾

using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
using namespace YActor;
using namespace YDrawer;
using namespace YParticle;
using namespace YTransition;

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

	plainT_		 = pTexManager_->Load("white1x1.png", false);

	playerT_	 = pTexManager_->Load("player.png", true);
	enemyT_		 = pTexManager_->Load("e.png", false);

	mapT_		 = pTexManager_->Load("map.png", false);
	mapDispT_	 = pTexManager_->Load("mapDisp.png", false);

	// ----- �I�[�f�B�I ----- //

	//aA_ = pAudioManager_->Load("Resources/Audios/fanfare.wav");

	// ----- �X�v���C�g ----- //

	windowS_.reset(Sprite2D::Create({ WinSize }, { plainT_ }));
	curtenS_.reset(Sprite2D::Create({ WinSize }, { plainT_ }));
	mapDispS_.reset(Sprite2D::Create({ {32,32} }, { mapDispT_ }));

	// ------- ���f�� ------- //

	cubeM_.reset(Model::Create());
	skydomeM_.reset(Model::Load({ "skydome/", "skydome.obj", false, }));
	slimeM_.reset(Model::Load({ "slime/", "slime.obj", false, }));

	zundamonM_.reset(Model::Load({ "zundamon/", "zundamon.pmx", false, }));

	// ----- �r���{�[�h ----- //

	//debriB_.reset(Sprite3D::Create(false));

	// ------- �}�b�v ------- //

	mapMan_.Load({ cubeM_.get(), mapT_, mapDispS_.get() });

	// ----- �ÓI������ ----- //

	Blackout::StaticInitialize({ curtenS_.get() });
	Floor::StaticIntialize({ cubeM_.get(), plainT_ });

	Character::SetMapChipPointer({ mapMan_.CurrentMapPointer(), &particleMan_ });

	ParticleManager::StaticInitialize({ cubeM_.get()});
	PlayerDrawerCommon::StaticInitialize({});
}
#pragma endregion


#pragma region ������
void GameScene::Initialize()
{
	// ����������
	Srand();

	// �v���C���[
	//player_.Initialize({ {}, YMath::AdjustAngle({0,0,-1}), {10.0f,10.0f,10.0f} });
	player_.Initialize({ {}, YMath::AdjustAngle({0,0,1}), {10.0f,10.0f,10.0f} });
	playerDra_.Initialize(&player_.m_);

	// �}�b�v������
	mapMan_.Initialize({ 0, {}, { 25.0f, 7.5f, 7.5f } });

	// �V��������
	skydome_.Initialize(&player_.pos_, skydomeM_.get());

	// �J����������
	cameraMan_.Initialize();
	cameraMan_.SetFollowPoint(&player_.pos_);

	// �r���[�v���W�F�N�V����������
	vp_.Initialize({});

	// �A�^������}�l�[�W���[������
	collMan_.Initialize();

	// �p�[�e�B�N���}�l�[�W���[������
	particleMan_.Initialize();

	// �V�[���}�l�[�W���[������
	sceneMan_.Initialize();
	
}
#pragma endregion


#pragma region �X�V
void GameScene::Update()
{
	// �z�b�g�����[�h
	if (keys_->IsTrigger(DIK_L))
	{
		mapMan_.Load({ cubeM_.get(), mapDispT_, mapDispS_.get() });
		mapMan_.Reset();
	}

	// ���Z�b�g
	if (keys_->IsTrigger(DIK_R))
	{
		collMan_.Initialize();
	}

	// �v���C���[
	player_.rota_.y_ += 0.005f;
	player_.UpdateMatrix();
	playerDra_.Update();

	// �}�b�v�}�l�[�W���[
	mapMan_.Update();

	// �J����
	cameraMan_.Update();

	// �r���[�v���W�F�N�V����
	vp_ = cameraMan_.GetViewProjection();
	vp_.Update();

	// �p�[�e�B�N���}�l�[�W���[
	particleMan_.Update();

	// �X�J�C�h�[��
	skydome_.Update();

	// �V�[���}�l�[�W���[
	sceneMan_.Update();

	// �A�^������}�l�[�W���[
	collMan_.Update();

}
#pragma endregion


#pragma region �`��
void GameScene::DrawBackSprite2Ds()
{
	
}

void GameScene::DrawModels()
{
	// �V��
	//skydome_.Draw(vp_);

	// map
	//mapMan_.Draw(vp_);

	playerDra_.Draw(vp_);

	particleMan_.Draw(vp_);
}

void GameScene::DrawSprite3Ds()
{
	
}

void GameScene::DrawFrontSprite2Ds()
{
	// map
	//mapMan_.Draw2D();

	// scene
	//sceneMan_.Draw();
}

void GameScene::Draw()
{
	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- �w�i�X�v���C�g ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	ModelCommon::StaticSetDrawCommand();
	// --------- ���f�� --------- //

	DrawModels();

	// -------------------------- //
	Sprite3DCommon::StaticSetDrawCommand();
	// ------- �r���{�[�h ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- �O�i�X�v���C�g ----- //

	DrawFrontSprite2Ds();
	
	// -------------------------- //
}
#pragma endregion