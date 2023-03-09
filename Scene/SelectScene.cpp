#include "SelectScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>

#pragma region 名前空間宣言
using YScene::SelectScene;
using namespace YGame;
#pragma endregion 

#pragma region Static関連
#pragma endregion 

#pragma region 読み込み
void SelectScene::Load()
{
	// ----- テクスチャ ----- //

	plainTex_ = pTexManager_->Load("white1x1.png", false);

	// ----- オーディオ ----- //

	//aA_ = pAudioManager_->Load("Resources/Audios/fanfare.wav");

	// ----- スプライト (2D) ----- //

	windowSpr_.reset(Sprite2D::Create({ WinSize }, { plainTex_ }));

	// ----- スプライト (3D) ----- //

	//debriB_.reset(Sprite3D::Create(false));

	// ------- モデル ------- //

	cubeMod_.reset(Model::Create());

	// ----- 静的初期化 ----- //
}
#pragma endregion


#pragma region 初期化
void SelectScene::Initialize()
{
	// ライト初期化
	lightGroup_.reset(LightGroup::Create());

	// ビュープロジェクション初期化
	vp_.Initialize({});
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
		SceneManager::GetInstance()->Change("PLAY");
	}

	// ビュープロジェクション
	vp_.Update();
}
#pragma endregion


#pragma region 描画
void SelectScene::DrawBackSprite2Ds()
{

}

void SelectScene::DrawModels()
{

}

void SelectScene::DrawSprite3Ds()
{

}

void SelectScene::DrawFrontSprite2Ds()
{

}

void SelectScene::Draw()
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