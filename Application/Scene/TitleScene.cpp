#include "TitleScene.h"
#include "SceneExecutive.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#pragma region ���O��Ԑ錾

using YScene::TitleScene;
using namespace YInput;
using namespace YGame;
using namespace YMath;

#pragma endregion 

#pragma region Static�֘A
#pragma endregion 


#pragma region �ǂݍ���
void TitleScene::Load()
{
}
#pragma endregion


#pragma region ������
void TitleScene::Initialize()
{
	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize();
}
#pragma endregion


#pragma region �I������
void TitleScene::Finalize()
{

}
#pragma endregion


#pragma region �X�V
void TitleScene::Update()
{
	// �r���[�v���W�F�N�V�����X�V
	transferVP_.UpdateMatrix();
}
#pragma endregion


#pragma region �`��
void TitleScene::Draw()
{
}
#pragma endregion