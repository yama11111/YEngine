#include "TitleScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>

#pragma region 名前空間宣言
using YScene::TitleScene;
using namespace YGame;
#pragma endregion 

#pragma region Static関連
#pragma endregion 

#pragma region 読み込み
void TitleScene::Load()
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
void TitleScene::Initialize()
{
	// ライト初期化
	lightGroup_.reset(LightGroup::Create());

	// ビュープロジェクション初期化
	vp_.Initialize({});
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
		SceneManager::GetInstance()->Change("SELECT");
	}
	

	// ビュープロジェクション
	vp_.Update();
}
#pragma endregion


#pragma region 描画
void TitleScene::DrawBackSprite2Ds()
{

}

void TitleScene::DrawModels()
{
	
}

void TitleScene::DrawSprite3Ds()
{

}

void TitleScene::DrawFrontSprite2Ds()
{
	
}

void TitleScene::Draw()
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