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
	Level::ClearAllData();
	
	Level::LoadAsset();
	
	pLevel_ = Level::LoadJson("levelData.json");
	pLevel_->Initialize();
}
#pragma endregion


#pragma region ������
void TestScene::Initialize()
{
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
	pLevel_->Update();
}
#pragma endregion


#pragma region �`��
void TestScene::Draw()
{
	pLevel_->Draw();
}
#pragma endregion