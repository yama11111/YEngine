#include "TitleScene.h"
#include "SceneExecutive.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#pragma region 名前空間宣言

using YScene::TitleScene;
using namespace YInput;
using namespace YGame;
using namespace YMath;

#pragma endregion 

#pragma region Static関連
#pragma endregion 


#pragma region 読み込み
void TitleScene::Load()
{
}
#pragma endregion


#pragma region 初期化
void TitleScene::Initialize()
{
	// ビュープロジェクション初期化
	transferVP_.Initialize();
}
#pragma endregion


#pragma region 終了処理
void TitleScene::Finalize()
{

}
#pragma endregion


#pragma region 更新
void TitleScene::Update()
{
	// ビュープロジェクション更新
	transferVP_.UpdateMatrix();
}
#pragma endregion


#pragma region 描画
void TitleScene::Draw()
{
}
#pragma endregion