#include "PlayScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>

#pragma region ���O��Ԑ錾
using YScene::PlayScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
//using namespace YActor;
using namespace YDrawer;
//using namespace YParticle;
//using namespace YTransition;
#pragma endregion 

#pragma region Static�֘A
#pragma endregion 

#pragma region �ǂݍ���
void PlayScene::Load()
{
	// ----- �e�N�X�`�� ----- //

	plainT_		 = pTexManager_->Load("white1x1.png", false);

	playerT_	 = pTexManager_->Load("player.png", true);
	enemyT_		 = pTexManager_->Load("enemy.png", false);

	mapT_		 = pTexManager_->Load("map.png", false);
	mapDispT_	 = pTexManager_->Load("mapDisp.png", false);

	// ----- �I�[�f�B�I ----- //

	//aA_ = pAudioManager_->Load("Resources/Audios/fanfare.wav");

	// ----- �X�v���C�g (2D) ----- //

	windowS_.reset(Sprite2D::Create({ WinSize }, { plainT_ }));
	curtenS_.reset(Sprite2D::Create({ WinSize }, { plainT_ }));
	mapDispS_.reset(Sprite2D::Create({ {32,32} }, { mapDispT_ }));

	// ----- �X�v���C�g (3D) ----- //

	//debriB_.reset(Sprite3D::Create(false));
	
	// ------- ���f�� ------- //

	cubeM_.reset(Model::Create());
	skydomeM_.reset(Model::Load({ "skydome/", "skydome.obj", false, }));
	slimeM_.reset(Model::Load({ "slime/", "slime.obj", false, }));

	zundamonM_.reset(Model::Load({ "zundamon/", "zundamon.pmx", false, }));

	// ------- �}�b�v ------- //

	mapMan_.Load({ cubeM_.get(), mapT_, mapDispS_.get() });

	// ----- �ÓI������ ----- //

	//Floor::StaticIntialize({ cubeM_.get(), plainT_ });

	//Character::SetMapChipPointer({ mapMan_.CurrentMapPointer(), &particleMan_ });

	//ParticleManager::StaticInitialize({ cubeM_.get()});
	PlayerDrawerCommon::StaticInitialize({});


	playerS_.reset(Sprite2D::Create({ {128,128} }, { playerT_ }));
	enemyS_.reset(Sprite2D::Create({ {128,128} }, { enemyT_ }));
}
#pragma endregion


#pragma region ������
void PlayScene::Initialize()
{
	// �v���C���[
	player_.reset(ObjectModel::Create({ {+20,0,0}, YMath::AdjustAngle({0,0,1}), {10.0f,10.0f,10.0f} }));
	playerDra_.Initialize(&player_->m_);

	sphere_.center_ = { 0,2,0 };
	sphere_.SafeSetRadius(1.0f);

	plane_.SafeSetNormal({ 0,1,0 });
	plane_.distance_ = 0.0f;

	triangle_.p0_ = { -1.0f,0,-1.0f };
	triangle_.p1_ = { -1.0f,0,+1.0f };
	triangle_.p2_ = { +1.0f,0,-1.0f };
	triangle_.SafeSetNormal({ 0.0f,1.0f,0.0f });

	// �}�b�v������
	mapMan_.Initialize({ 0, {}, { 25.0f, 7.5f, 7.5f } });

	// �V��������
	//skydome_.Initialize(&player_.pos_, skydomeM_.get());

	// �J����������
	cameraMan_.Initialize();
	cameraMan_.SetFollowPoint(&player_->pos_);

	// ���C�g������
	lightGroup_.reset(LightGroup::Create());

	// �r���[�v���W�F�N�V����������
	vp_.Initialize({});

	// �A�^������}�l�[�W���[������
	collMan_.Initialize();

	// �p�[�e�B�N���}�l�[�W���[������
	//particleMan_.Initialize();
}
#pragma endregion

#pragma region �I������
void PlayScene::Finalize()
{
	lightGroup_.reset();
}
#pragma endregion

#pragma region �X�V
void PlayScene::Update()
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

	// ���̃V�[����
	if (keys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("RESULT");
	}

	// �v���C���[
	player_->rota_.y_ += 0.005f;
	player_->UpdateMatrix();
	playerDra_.Update();

	// �}�b�v�}�l�[�W���[
	mapMan_.Update();

	sphere_.center_.x_ += 0.1f * keys_->Horizontal();
	sphere_.center_.y_ += 0.1f * keys_->Vertical();

	YCollision::CollisonPlaneSphere(plane_, sphere_);
	YCollision::CollisionTriangleSphere(triangle_, sphere_);

	// �J����
	cameraMan_.Update();

	// �r���[�v���W�F�N�V����
	vp_ = cameraMan_.GetViewProjection();
	vp_.Update();

	// �p�[�e�B�N���}�l�[�W���[
	//particleMan_.Update();

	// �X�J�C�h�[��
	//skydome_.Update();

	// �A�^������}�l�[�W���[
	collMan_.Update();
}
#pragma endregion


#pragma region �`��
void PlayScene::DrawBackSprite2Ds()
{
	
}

void PlayScene::DrawModels()
{
	// �V��
	//skydome_.Draw(vp_, lightGroup_.get());

	// �}�b�v�`�b�v
	//mapMan_.Draw(vp_);

	playerDra_.Draw(vp_, lightGroup_.get());

	// �p�[�e�B�N��
	//particleMan_.Draw(vp_);
}

void PlayScene::DrawSprite3Ds()
{
	
}

void PlayScene::DrawFrontSprite2Ds()
{
	// �}�b�v�`�b�v
	//mapMan_.Draw2D();
}

void PlayScene::Draw()
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