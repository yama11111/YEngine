#include "PlayScene.h"
#include "SceneExecutive.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

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

}
#pragma endregion


#pragma region ������
void PlayScene::Initialize()
{

	// �r���[�v���W�F�N�V����������
	transferVP_.Initialize();
	transferVP_.eye_ = Vector3(0, +2.5f, -20.0f);
}
#pragma endregion


#pragma region �I������
void PlayScene::Finalize()
{
}
#pragma endregion


#pragma region �X�V
void PlayScene::Update()
{
	// �r���[�v���W�F�N�V�����X�V
	transferVP_.UpdateMatrix();
}
#pragma endregion


#pragma region �`��
void PlayScene::Draw()
{
}
#pragma endregion