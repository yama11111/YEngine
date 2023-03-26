#include "PlayScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include "imgui.h"

#pragma region ���O��Ԑ錾
using YScene::PlayScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
#pragma endregion 

#pragma region Static�֘A
#pragma endregion 

#pragma region �ǂݍ���
void PlayScene::Load()
{
	// ----- �e�N�X�`�� ----- //

	plainTex_ = spTexManager_->Load("white1x1.png", false);

	// ----- �I�[�f�B�I ----- //

	//aA_ = pAudioManager_->Load("Resources/Audios/fanfare.wav");

	// ----- �X�v���C�g (2D) ----- //

	windowSpr_.reset(Sprite2D::Create({ WinSize }, { plainTex_ }));

	// ----- �X�v���C�g (3D) ----- //

	
	// ------- ���f�� ------- //

	cubeMod_.reset(Model::Create());

	// ----- �ÓI������ ----- //

}
#pragma endregion


#pragma region ������
void PlayScene::Initialize()
{
	// ���C�g������
	lightGroup_.reset(LightGroup::Create());
	{
		lightGroup_->SetDirectionalLightActive(0, false);
		lightGroup_->SetDirectionalLightActive(1, false);
		lightGroup_->SetDirectionalLightActive(2, false);
	}
	{
		lightGroup_->SetPointLightActive(0, false);
		lightGroup_->SetPointLightActive(1, false);
		lightGroup_->SetPointLightActive(2, false);
	}

	// �r���[�v���W�F�N�V����������
	vp_.Initialize({ {0,5,-15} });
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
	// ���Z�b�g
	if (sKeys_->IsTrigger(DIK_R))
	{
	}

	// ���̃V�[����
	if (sKeys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("RESULT");
	}

	// �r���[�v���W�F�N�V����
	vp_.UpdateMatrix();
}
#pragma endregion


#pragma region �`��
void PlayScene::DrawBackSprite2Ds()
{
	
}

void PlayScene::DrawBackSprite3Ds()
{
}

void PlayScene::DrawModels()
{

}

void PlayScene::DrawFrontSprite3Ds()
{

}

void PlayScene::DrawFrontSprite2Ds()
{

}

void PlayScene::Draw()
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