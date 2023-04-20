#include "ResultScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>

#pragma region 名前空間宣言
using YScene::ResultScene;
using namespace YGame;
using namespace YMath;
#pragma endregion 

#pragma region Static関連
#pragma endregion 

#pragma region 読み込み
void ResultScene::Load()
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
void ResultScene::Initialize()
{

}
#pragma endregion

#pragma region 終了処理
void ResultScene::Finalize()
{

}
#pragma endregion

#pragma region 更新
void ResultScene::Update()
{

}
#pragma endregion


#pragma region 描画
void ResultScene::DrawBackSprite2Ds()
{
	
}

void ResultScene::DrawModels()
{

}

void ResultScene::DrawSprite3Ds()
{

}

void ResultScene::DrawFrontSprite2Ds()
{
	
}

void ResultScene::Draw()
{
	// -------------------------- //
	Sprite2D::Pipeline::StaticSetDrawCommond();
	// ----- 背景スプライト ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	Model::Pipeline::StaticSetDrawCommond();
	// --------- モデル --------- //

	DrawModels();

	// -------------------------- //
	Sprite3D::Pipeline::StaticSetDrawCommond();
	// ------- ビルボード ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2D::Pipeline::StaticSetDrawCommond();
	// ----- 前景スプライト ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion