#include "SelectScene.h"
#include "SceneExecutive.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#pragma region 名前空間宣言

using YGame::SelectScene;
using namespace YGame;

#pragma endregion 

#pragma region Static関連
#pragma endregion 


#pragma region 読み込み
void SelectScene::Load()
{
}
#pragma endregion


#pragma region 初期化
void SelectScene::Initialize()
{
	// ビュープロジェクション初期化
	transferVP_.Initialize();
}
#pragma endregion


#pragma region 終了処理
void SelectScene::Finalize()
{
}
#pragma endregion


#pragma region 更新
void SelectScene::Update()
{
	// ビュープロジェクション更新
	transferVP_.UpdateMatrix();
}
#pragma endregion


#pragma region 描画

void SelectScene::Draw()
{
}
#pragma endregion