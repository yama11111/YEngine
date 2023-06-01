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
}
#pragma endregion


#pragma region 初期化
void TestScene::Initialize()
{
	// ビュープロジェクション初期化
	transferVP_.Initialize();
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
	// ビュープロジェクション更新
	transferVP_.UpdateMatrix();
}
#pragma endregion


#pragma region 描画
void TestScene::Draw()
{
}
#pragma endregion