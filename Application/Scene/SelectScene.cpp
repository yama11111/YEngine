#include "SelectScene.h"
#include "SceneExecutive.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#pragma region ���O��Ԑ錾

using YGame::SelectScene;
using namespace YGame;

#pragma endregion 

#pragma region Static�֘A
#pragma endregion 


#pragma region �ǂݍ���
void SelectScene::Load()
{
}
#pragma endregion


#pragma region ������
void SelectScene::Initialize()
{
	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize();
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
	// �r���[�v���W�F�N�V�����X�V
	transferVP_.UpdateMatrix();
}
#pragma endregion


#pragma region �`��

void SelectScene::Draw()
{
}
#pragma endregion