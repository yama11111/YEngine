#include "TestScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#pragma region 名前空間宣言

using YScene::TestScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

#pragma endregion 


#pragma region Static関連

#pragma endregion 


#pragma region 読み込み
void TestScene::Load()
{
	Level::ClearAllData();
	
	Level::LoadAsset();
	
	pLevel_ = Level::LoadJson("levelData.json");
	pLevel_->Initialize();
}
#pragma endregion


#pragma region 初期化
void TestScene::Initialize()
{
}
#pragma endregion


#pragma region 終了処理
void TestScene::Finalize()
{
}
#pragma endregion


#pragma region 更新
void TestScene::Update()
{
	pLevel_->Update();
}
#pragma endregion


#pragma region 描画
void TestScene::Draw()
{
	pLevel_->Draw();
}
#pragma endregion