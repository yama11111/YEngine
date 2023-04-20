#include "EditScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#pragma region ���O��Ԑ錾
using YScene::EditScene;
using namespace YGame;
#pragma endregion 

#pragma region Static�֘A
#pragma endregion 

#pragma region �ǂݍ���
void EditScene::Load()
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
void EditScene::Initialize()
{

}
#pragma endregion

#pragma region �I������
void EditScene::Finalize()
{

}
#pragma endregion

#pragma region �X�V
void EditScene::Update()
{

}
#pragma endregion


#pragma region �`��
void EditScene::DrawBackSprite2Ds()
{

}

void EditScene::DrawModels()
{

}

void EditScene::DrawSprite3Ds()
{

}

void EditScene::DrawFrontSprite2Ds()
{

}

void EditScene::Draw()
{
	// -------------------------- //
	Sprite2D::Pipeline::StaticSetDrawCommond();
	// ----- �w�i�X�v���C�g ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	Model::Pipeline::StaticSetDrawCommond();
	// --------- ���f�� --------- //

	DrawModels();

	// -------------------------- //
	Sprite3D::Pipeline::StaticSetDrawCommond();
	// ------- �r���{�[�h ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2D::Pipeline::StaticSetDrawCommond();
	// ----- �O�i�X�v���C�g ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion