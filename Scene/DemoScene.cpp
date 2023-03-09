#include "DemoScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include "imgui.h"

#pragma region ���O��Ԑ錾
using YScene::DemoScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
#pragma endregion 

#pragma region Static�֘A
#pragma endregion 

#pragma region �ǂݍ���
void DemoScene::Load()
{
	// ----- �e�N�X�`�� ----- //

	plainTex_ = pTexManager_->Load("white1x1.png", false);

	mapDispTex_ = pTexManager_->Load("mapDisp.png", false);
	mapTex_ = pTexManager_->Load("map.png", false);

	// ----- �I�[�f�B�I ----- //

	// ----- �X�v���C�g (2D) ----- //

	windowSpr_.reset(Sprite2D::Create({ WinSize }, { plainTex_ }));
	mapDispSpr_.reset(Sprite2D::Create({ {32,32} }, { mapDispTex_ }));

	// ----- �X�v���C�g (3D) ----- //

	// ------- ���f�� ------- //

	cubeMod_.reset(Model::Create());
	skydomeMod_.reset(Model::Load({ "skydome/", "skydome.obj", false, }));

	buildingMod_.reset(Model::Load({ "building/", "building.obj", false, }));

	// ------- �}�b�v ------- //

	mapMan_.Load({ { cubeMod_.get() }, { mapDispSpr_.get() } });

	// ----- �ÓI������ ----- //

	Character::StaticInitialize({ mapMan_.CurrentMapPointer(), &particleMan_ });
	Player::StaticIntialize({ cubeMod_.get(), plainTex_});
	FireSpark::StaticInitialize({ cubeMod_.get() });
}
#pragma endregion


#pragma region ������
void DemoScene::Initialize()
{
	// �v���C���[
	player_.Initialize({ {+100,-100,0}, YMath::AdjustAngle({0,0,1}), {10.0f,10.0f,10.0f} });

	Vector3 center_ = Vector3(0, -40, 60);

	buildings_[0].reset(ObjectModel::Create({ center_ + Vector3(-120.0f, -60.0f, -100.0f), {}, {15.0f,15.0f,15.0f} }));
	buildings_[1].reset(ObjectModel::Create({ center_ + Vector3(-100.0f, -60.0f, -60.0f), {}, {20.0f,20.0f,20.0f} }));
	buildings_[2].reset(ObjectModel::Create({ center_ + Vector3(-100.0f, -60.0f, -40.0f), {}, {15.0f,15.0f,15.0f} }));
	buildings_[3].reset(ObjectModel::Create({ center_ + Vector3(-80.0f, -60.0f, -20.0f), {}, {10.0f,10.0f,10.0f} }));
	buildings_[4].reset(ObjectModel::Create({ center_ + Vector3(-140.0f, -60.0f, -10.0f), {}, {10.0f,10.0f,10.0f} }));
	buildings_[5].reset(ObjectModel::Create({ center_ + Vector3(-120.0f, -60.0f, +20.0f), {}, {25.0f,25.0f,25.0f} }));
	buildings_[6].reset(ObjectModel::Create({ center_ + Vector3(-80.0f, -60.0f, +60.0f), {}, {15.0f,15.0f,15.0f} }));
	buildings_[7].reset(ObjectModel::Create({ center_ + Vector3(-140.0f, -60.0f, +120.0f), {}, {10.0f,10.0f,10.0f} }));
	buildingColor_.reset(Color::Create({ 1.0f,1.0f,1.0f,1.0f }));

	// �}�b�v������
	mapMan_.Initialize({ 0, {}, { 10.0f, 10.0f, 10.0f } });

	// �V��������
	skydome_.Initialize({ center_, {}, {600.0f,600.0f,600.0f} }, skydomeMod_.get());

	// �J����������
	cameraMan_.Initialize(player_.PosPointer());

	// ���C�g������
	lightGroup_.reset(LightGroup::Create());
	{
		lightGroup_->SetDirectionalLightActive(0, false);
		lightGroup_->SetDirectionalLightDirection(0, { +1.0f,-1.0f, 0.0f });
		lightGroup_->SetDirectionalLightColor(0, { 1.0f,1.0f,1.0f });

		lightGroup_->SetDirectionalLightActive(1, false);
		lightGroup_->SetDirectionalLightDirection(1, { +0.5f,+0.1f,+0.2f });
		lightGroup_->SetDirectionalLightColor(1, { 1.0f,1.0f,1.0f });

		lightGroup_->SetDirectionalLightActive(2, false);
		lightGroup_->SetDirectionalLightDirection(2, { -0.5f,+0.1f,-0.2f });
		lightGroup_->SetDirectionalLightColor(2, { 1.0f,1.0f,1.0f });
	}
	{
		lightGroup_->SetPointLightActive(0, true);
		lightGroup_->SetPointLightPos(0, center_ + Vector3(-60.0f, -80.0f, -40.0f));
		lightGroup_->SetPointLightAtten(0, { 0.0001f,0.0001f,0.0001f });
		lightGroup_->SetPointLightColor(0, { 0.75f,0.25f,0.25f });

		lightGroup_->SetPointLightActive(1, true);
		lightGroup_->SetPointLightPos(1, center_ + Vector3(-60.0f, -80.0f, +40.0f));
		lightGroup_->SetPointLightAtten(1, { 0.0001f,0.0001f,0.0001f });
		lightGroup_->SetPointLightColor(1, { 0.75f,0.25f,0.25f });

		lightGroup_->SetPointLightActive(2, true);
		lightGroup_->SetPointLightPos(2, center_ + Vector3(-140.0f, -80.0f, -20.0f));
		lightGroup_->SetPointLightAtten(2, { 0.0001f,0.0001f,0.0001f });
		lightGroup_->SetPointLightColor(2, { 0.75f,0.25f,0.25f });
	}

	lightGroup2_.reset(LightGroup::Create());
	{
		lightGroup2_->SetDirectionalLightActive(0, true);
		lightGroup2_->SetDirectionalLightDirection(0, { +1.0f,+1.0f, 0.0f });
		lightGroup2_->SetDirectionalLightColor(0, { 1.00f,1.00f,1.00f });

		lightGroup2_->SetDirectionalLightActive(1, true);
		lightGroup2_->SetDirectionalLightDirection(1, { -1.0f,+1.0f,+1.0f });
		lightGroup2_->SetDirectionalLightColor(1, { 1.00f,1.00f,1.00f });

		lightGroup2_->SetDirectionalLightActive(2, true);
		lightGroup2_->SetDirectionalLightDirection(2, { +1.0f,+1.0f,+1.0f });
		lightGroup2_->SetDirectionalLightColor(2, { 1.00f,1.00f,1.00f });
	}
	{
		lightGroup2_->SetPointLightActive(0, true);
		lightGroup2_->SetPointLightPos(0, {});
		lightGroup2_->SetPointLightAtten(0, { 0.0025f,0.0025f,0.0025f });
		lightGroup2_->SetPointLightColor(0, { 0.25f,0.75f,0.75f });

		lightGroup2_->SetPointLightActive(1, true);
		lightGroup2_->SetPointLightPos(1, {});
		lightGroup2_->SetPointLightAtten(1, { 0.0025f,0.0025f,0.0025f });
		lightGroup2_->SetPointLightColor(1, { 0.25f,0.75f,0.75f });

		lightGroup2_->SetPointLightActive(2, true);
		lightGroup2_->SetPointLightPos(2, {});
		lightGroup2_->SetPointLightAtten(2, { 0.0025f,0.0025f,0.0025f });
		lightGroup2_->SetPointLightColor(2, { 0.25f,0.75f,0.75f });
	}

	// �r���[�v���W�F�N�V����������
	vp_.Initialize({});

	// �A�^������}�l�[�W���[������
	collMan_.Initialize();

	// �p�[�e�B�N���}�l�[�W���[������
	particleMan_.Initialize();
}
#pragma endregion

#pragma region �I������
void DemoScene::Finalize()
{
	lightGroup_.reset();
}
#pragma endregion

#pragma region �X�V
void DemoScene::Update()
{
	// �z�b�g�����[�h
	if (keys_->IsTrigger(DIK_L))
	{
		mapMan_.Load({ { cubeMod_.get() }, { mapDispSpr_.get() } });
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
	player_.Update();

	for (size_t i = 0; i < buildings_.size(); i++)
	{
		buildings_[i]->UpdateMatrix();
	}

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

	// �A�^������}�l�[�W���[
	collMan_.Update();
}
#pragma endregion


#pragma region �`��
void DemoScene::DrawBackSprite2Ds()
{

}

void DemoScene::DrawBackSprite3Ds()
{
}

void DemoScene::DrawModels()
{
	// �V��
	skydome_.Draw(vp_, lightGroup_.get());

	// �r��
	for (size_t i = 0; i < buildings_.size(); i++)
	{
		buildingMod_->Draw(buildings_[i].get(), vp_, lightGroup_.get(), buildingColor_.get());
	}

	// �}�b�v�`�b�v
	mapMan_.Draw(vp_, lightGroup2_.get(), plainTex_);
	
	// �v���C���[
	player_.Draw(vp_, lightGroup2_.get());


	// �p�[�e�B�N��
	particleMan_.Draw(vp_, lightGroup2_.get());
}

void DemoScene::DrawFrontSprite3Ds()
{

}

void DemoScene::DrawFrontSprite2Ds()
{
	// �}�b�v�`�b�v
	//mapMan_.Draw2D();
}

void DemoScene::Draw()
{
	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- �w�i�X�v���C�g2D----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	Sprite3DCommon::StaticSetDrawCommand();
	// ----- �O�i�X�v���C�g3D ----- //

	DrawBackSprite3Ds();

	// -------------------------- //
	ModelCommon::StaticSetDrawCommand();
	// --------- ���f�� --------- //

	DrawModels();

	// -------------------------- //
	Sprite3DCommon::StaticSetDrawCommand();
	// ----- �O�i�X�v���C�g3D ----- //

	DrawFrontSprite3Ds();

	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- �O�i�X�v���C�g2D ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion