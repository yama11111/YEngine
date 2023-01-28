#include "GameScene.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>

#pragma region ���O��Ԑ錾

using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YTransition;
using namespace YGame;

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

	//playerT_	 = pTexManager_->Load("player.png", true);
	//enemyT_	 = pTexManager_->Load("enemy.png", true);

	playerT_	 = pTexManager_->Load("player.png", true);
	enemyT_		 = pTexManager_->Load("e.png", false);

	mapT_		 = pTexManager_->Load("map.png", false);
	mapDispT_	 = pTexManager_->Load("mapDisp.png", false);

	//debriT_		 = pTexManager_->Load("debri.png", true);

	// ----- �I�[�f�B�I ----- //

	//aA_ = pAudioManager_->Load("Resources/Audios/fanfare.wav");

	// ----- �X�v���C�g ----- //

	windowS_.reset(Sprite::Create({ WinSize }, { plainT_ }));
	curtenS_.reset(Sprite::Create({ WinSize }, { plainT_ }));
	mapDispS_.reset(Sprite::Create({ {32,32} }, { mapDispT_ }));

	// ------- ���f�� ------- //

	cubeM_.reset(Model::Create());
	skydomeM_.reset(Model::Load({ "skydome/", "skydome.obj", false, false  }));
	slimeM_.reset(Model::Load({ "slime/", "slime.obj", false, false }));

	//playerMods_[static_cast<size_t>(Parts::Body)].reset(
	//	Model::Load({ "player_body/", "player_body.obj", false, false }));
	//playerMods_[static_cast<size_t>(Parts::Face)].reset(
	//	Model::Load({ "player_tail/", "player_tail.obj", false, false }));
	//playerMods_[static_cast<size_t>(Parts::Tail)].reset(
	//	Model::Load({ "player_face/", "player_face.obj", false, false }));

	playerMods_[static_cast<size_t>(Parts::Body)].reset(
		Model::Load({ "player/player_body/", "player_body.obj", false, false }));
	playerMods_[static_cast<size_t>(Parts::Face)].reset(
		Model::Load({ "player/player_tail/", "player_tail.obj", false, false }));
	playerMods_[static_cast<size_t>(Parts::Tail)].reset(
		Model::Load({ "player/player_face/", "player_face.obj", false, false }));

	// ----- �r���{�[�h ----- //

	//debriB_.reset(Billboard::Create(false));

	// ------- �}�b�v ------- //

	mapMan_.Load({ cubeM_.get(), mapT_, mapDispS_.get() });

	// ----- �ÓI������ ----- //

	Blackout::StaticInitialize({ curtenS_.get() });
	Floor::StaticIntialize({ cubeM_.get(), plainT_ });

	Character::SetMapChipPointer({ mapMan_.CurrentMapPointer(), &particleMan_ });

	YParticle::ParticleManager::StaticInitialize({ cubeM_.get()});
}
#pragma endregion


#pragma region ������
void GameScene::Initialize()
{
	// ����������
	Srand();

	// �v���C���[
	player_.Initialize({ {}, YMath::AdjustAngle({0,0,-1}), {10.0f,10.0f,10.0f} });
	for (size_t i = 0; i < playerModTranss_.size(); i++)
	{
		playerModTranss_[i].Initialize({});
		playerModTranss_[i].SetParent(&player_.m_);
	}
	playerModTranss_[static_cast<size_t>(Parts::Tail)].pos_ = { 0,0,-1.75f };

	// �}�b�v������
	mapMan_.Initialize({ 0, {}, { 25.0f, 7.5f, 7.5f } });

	// �V��������
	skydome_.Initialize(&player_.pos_, skydomeM_.get());

	// �J����������
	cameraMan_.SetFollowPoint(&player_.pos_);
	cameraMan_.Initialize();

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
	player_.Update();
	for (size_t i = 0; i < playerModTranss_.size(); i++)
	{
		playerModTranss_[i].Update();
	}

	// �}�b�v�}�l�[�W���[
	mapMan_.Update();

	// �J����
	cameraMan_.Update();

	// �r���[�v���W�F�N�V����
	//vp_ = cameraMan_.GetViewProjection();
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
void GameScene::DrawBackSprites()
{
	
}

void GameScene::DrawModels()
{
	// �V��
	//skydome_.Draw(vp_);

	// map
	//mapMan_.Draw(vp_);

	for (size_t i = 0; i < playerModTranss_.size(); i++)
	{
		playerMods_[i]->Draw(playerModTranss_[i], vp_);
	}

	particleMan_.Draw(vp_);
}

void GameScene::DrawBillboards()
{
	
}

void GameScene::DrawFrontSprites()
{
	// map
	mapMan_.Draw2D();

	// scene
	sceneMan_.Draw();
}

void GameScene::Draw()
{
	// -------------------------- //
	SpriteCommon::StaticSetDrawCommand();
	// ----- �w�i�X�v���C�g ----- //

	DrawBackSprites();

	// -------------------------- //
	ModelCommon::StaticSetDrawCommand();
	// --------- ���f�� --------- //

	DrawModels();

	// -------------------------- //
	BillboardCommon::StaticSetDrawCommand();
	// ------- �r���{�[�h ------- //

	DrawBillboards();

	// -------------------------- //
	SpriteCommon::StaticSetDrawCommand();
	// ----- �O�i�X�v���C�g ----- //

	DrawFrontSprites();
	
	// -------------------------- //
}
#pragma endregion