#include "SelectScene.h"
#include "SceneManager.h"
#include "TransitionManager.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

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

	// ----- �I�[�f�B�I ----- //

	// ----- �X�v���C�g (2D) ----- //

	// ----- �X�v���C�g (3D) ----- //

	// ------- ���f�� ------- //

	// ----- �ÓI������ ----- //

}
#pragma endregion


#pragma region ������
void SelectScene::Initialize()
{
	
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
	Sprite2D::Common::StaticSetPipeline();
	// ----- �w�i�X�v���C�g ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	Model::Common::StaticSetPipeline();
	// --------- ���f�� --------- //

	DrawModels();

	// -------------------------- //
	Sprite3D::Common::StaticSetPipeline();
	// ------- �r���{�[�h ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2D::Common::StaticSetPipeline();
	// ----- �O�i�X�v���C�g ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion