#include "TestScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#pragma region ���O��Ԑ錾

using YScene::TestScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

#pragma endregion 


#pragma region Static�֘A

#pragma endregion 


#pragma region �ǂݍ���
void TestScene::Load()
{
}
#pragma endregion


#pragma region ������
void TestScene::Initialize()
{
	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize();
}
#pragma endregion


#pragma region �I������
void TestScene::Finalize()
{
}
#pragma endregion


#pragma region �X�V
void TestScene::Update()
{
	// �r���[�v���W�F�N�V�����X�V
	transferVP_.UpdateMatrix();
}
#pragma endregion


#pragma region �`��
void TestScene::Draw()
{
}
#pragma endregion