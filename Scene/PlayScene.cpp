#include "PlayScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include "imgui.h"

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
	// ----- テクスチャ ----- //

	plainTex_ = spTexManager_->Load("white1x1.png", false);

	// ----- オーディオ ----- //

	//aA_ = pAudioManager_->Load("Resources/Audios/fanfare.wav");

	// ----- スプライト (2D) ----- //

	windowSpr_.reset(Sprite2D::Create({ WinSize }, { plainTex_ }));

	// ----- スプライト (3D) ----- //

	
	// ------- モデル ------- //

	cubeMod_.reset(Model::Create());

	// ----- 静的初期化 ----- //

}
#pragma endregion


#pragma region 初期化
void PlayScene::Initialize()
{
	// ライト初期化
	lightGroup_.reset(LightGroup::Create());
	{
		lightGroup_->SetDirectionalLightActive(0, false);
		lightGroup_->SetDirectionalLightActive(1, false);
		lightGroup_->SetDirectionalLightActive(2, false);
	}
	{
		lightGroup_->SetPointLightActive(0, false);
		lightGroup_->SetPointLightActive(1, false);
		lightGroup_->SetPointLightActive(2, false);
	}

	// ビュープロジェクション初期化
	vp_.Initialize({ {0,5,-15} });
}
#pragma endregion

#pragma region 終了処理
void PlayScene::Finalize()
{
	lightGroup_.reset();
}
#pragma endregion

#pragma region 更新
void PlayScene::Update()
{
	// リセット
	if (sKeys_->IsTrigger(DIK_R))
	{
	}

	// 次のシーンへ
	if (sKeys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("RESULT");
	}

	// ビュープロジェクション
	vp_.Update();
}
#pragma endregion


#pragma region 描画
void PlayScene::DrawBackSprite2Ds()
{
	
}

void PlayScene::DrawBackSprite3Ds()
{
}

void PlayScene::DrawModels()
{

}

void PlayScene::DrawFrontSprite3Ds()
{

}

void PlayScene::DrawFrontSprite2Ds()
{

}

void PlayScene::Draw()
{
	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- 背景スプライト2D----- //

	DrawBackSprite2Ds();

	// -------------------------- //
	Sprite3DCommon::StaticSetDrawCommand();
	// ----- 前景スプライト3D ----- //

	DrawBackSprite3Ds();

	// -------------------------- //
	ModelCommon::StaticSetDrawCommand();
	// --------- モデル --------- //

	DrawModels();

	// -------------------------- //
	Sprite3DCommon::StaticSetDrawCommand();
	// ----- 前景スプライト3D ----- //

	DrawFrontSprite3Ds();

	// -------------------------- //
	Sprite2DCommon::StaticSetDrawCommand();
	// ----- 前景スプライト2D ----- //

	DrawFrontSprite2Ds();
	
	// -------------------------- //
}
#pragma endregion