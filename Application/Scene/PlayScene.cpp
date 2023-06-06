#include "PlayScene.h"
#include "SceneExecutive.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#pragma region 名前空間宣言

using YScene::PlayScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

#pragma endregion 

#pragma region Static関連
#pragma endregion 


#pragma region 読み込み
void PlayScene::Load()
{

}
#pragma endregion


#pragma region 初期化
void PlayScene::Initialize()
{

	// ビュープロジェクション初期化
	transferVP_.Initialize();
	transferVP_.eye_ = Vector3(0, +2.5f, -20.0f);
}
#pragma endregion


#pragma region 終了処理
void PlayScene::Finalize()
{
}
#pragma endregion


#pragma region 更新
void PlayScene::Update()
{
	// ビュープロジェクション更新
	transferVP_.UpdateMatrix();
}
#pragma endregion


#pragma region 描画
void PlayScene::Draw()
{
}
#pragma endregion