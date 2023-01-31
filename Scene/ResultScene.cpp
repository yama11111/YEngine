#include "ResultScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>

#pragma region 名前空間宣言
using YScene::ResultScene;
using namespace YGame;
#pragma endregion 

#pragma region Static関連
#pragma endregion 

#pragma region 読み込み
void ResultScene::Load()
{
	// ----- テクスチャ ----- //

	plainT_ = pTexManager_->Load("white1x1.png", false);

	// ----- オーディオ ----- //

	//aA_ = pAudioManager_->Load("Resources/Audios/fanfare.wav");

	// ----- スプライト (2D) ----- //

	windowS_.reset(Sprite2D::Create({ WinSize }, { plainT_ }));

	// ----- スプライト (3D) ----- //

	//debriB_.reset(Sprite3D::Create(false));

	// ------- モデル ------- //

	cubeM_.reset(Model::Create());

	// ----- 静的初期化 ----- //
}
#pragma endregion


#pragma region 初期化
void ResultScene::Initialize()
{
	// ライト初期化
	lightGroup_.reset(LightGroup::Create());

	// ビュープロジェクション初期化
	vp_.Initialize({});
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
	// ホットリロード
	if (keys_->IsTrigger(DIK_L))
	{

	}

	// リセット
	if (keys_->IsTrigger(DIK_R))
	{

	}

	// 次のシーンへ
	if (keys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("TITLE");
	}

	// ビュープロジェクション
	vp_.Update();
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
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- 背景スプライト ----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	ModelCommon::StaticSetDrawCommand();
	// --------- モデル --------- //

	DrawModels();

	// -------------------------- //
	Sprite3DCommon::StaticSetDrawCommand();
	// ------- ビルボード ------- //

	DrawSprite3Ds();

	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- 前景スプライト ----- //

	DrawFrontSprite2Ds();

	// -------------------------- //
}
#pragma endregion