#include "EditScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#pragma region 名前空間宣言
using YScene::EditScene;
using namespace YGame;
#pragma endregion 

#pragma region Static関連
#pragma endregion 

#pragma region 読み込み
void EditScene::Load()
{
	// ----- テクスチャ ----- //

	// ----- オーディオ ----- //

	// ----- スプライト (2D) ----- //

	// ----- スプライト (3D) ----- //

	// ------- モデル ------- //

	// ----- 静的初期化 ----- //
}
#pragma endregion


#pragma region 初期化
void EditScene::Initialize()
{

}
#pragma endregion

#pragma region 終了処理
void EditScene::Finalize()
{

}
#pragma endregion

#pragma region 更新
void EditScene::Update()
{

}
#pragma endregion


#pragma region 描画
void EditScene::DrawBackSprite2Ds()
{

}

void EditScene::DrawModels()
{

}

void EditScene::DrawSprite3Ds()
{

}

void EditScene::DrawFrontSprite2Ds()
{

}

void EditScene::Draw()
{
	// -------------------------- //
	Sprite2D::Common::StaticSetPipeline();
	// ----- 背景スプライト ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	Model::Common::StaticSetPipeline();
	// --------- モデル --------- //

	DrawModels();

	// -------------------------- //
	Sprite3D::Common::StaticSetPipeline();
	// ------- ビルボード ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2D::Common::StaticSetPipeline();
	// ----- 前景スプライト ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion