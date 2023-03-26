#include "SelectScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>

#pragma region ���O��Ԑ錾
using YScene::SelectScene;
using namespace YGame;
#pragma endregion 

#pragma region Static�֘A
#pragma endregion 

#pragma region �ǂݍ���
void SelectScene::Load()
{
	// ----- �e�N�X�`�� ----- //

	plainTex_ = spTexManager_->Load("white1x1.png", false);

	// ----- �I�[�f�B�I ----- //

	//aA_ = pAudioManager_->Load("Resources/Audios/fanfare.wav");

	// ----- �X�v���C�g (2D) ----- //

	windowSpr_.reset(Sprite2D::Create({ WinSize }, { plainTex_ }));

	// ----- �X�v���C�g (3D) ----- //

	//debriB_.reset(Sprite3D::Create(false));

	// ------- ���f�� ------- //

	cubeMod_.reset(Model::Create());

	// ----- �ÓI������ ----- //
}
#pragma endregion


#pragma region ������
void SelectScene::Initialize()
{
	// ���C�g������
	lightGroup_.reset(LightGroup::Create());

	// �r���[�v���W�F�N�V����������
	vp_.Initialize({});
}
#pragma endregion

#pragma region �I������
void SelectScene::Finalize()
{

}
#pragma endregion

#pragma region �X�V
void SelectScene::Update()
{
	// �z�b�g�����[�h
	if (sKeys_->IsTrigger(DIK_L))
	{

	}

	// ���Z�b�g
	if (sKeys_->IsTrigger(DIK_R))
	{

	}

	// ���̃V�[����
	if (sKeys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("PLAY");
	}

	// �r���[�v���W�F�N�V����
	vp_.UpdateMatrix();
}
#pragma endregion


#pragma region �`��
void SelectScene::DrawBackSprite2Ds()
{

}

void SelectScene::DrawModels()
{

}

void SelectScene::DrawSprite3Ds()
{

}

void SelectScene::DrawFrontSprite2Ds()
{

}

void SelectScene::Draw()
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