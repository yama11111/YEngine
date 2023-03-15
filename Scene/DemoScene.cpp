#include "DemoScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include "imgui.h"

#pragma region 名前空間宣言
using YScene::DemoScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
#pragma endregion 

#pragma region Static関連
#pragma endregion 

#pragma region 読み込み
void DemoScene::Load()
{
	// ----- テクスチャ ----- //

	plainTex_ = spTexManager_->Load("white1x1.png", false);

	mapDispTex_ = spTexManager_->Load("mapDisp.png", false);
	mapTex_ = spTexManager_->Load("floar.png", false);

	// ----- オーディオ ----- //

	// ----- スプライト (2D) ----- //

	windowSpr_.reset(Sprite2D::Create({ WinSize }, { plainTex_ }));
	mapDispSpr_.reset(Sprite2D::Create({ {32,32} }, { mapDispTex_ }));

	// ----- スプライト (3D) ----- //

	filterSpr_.reset(Sprite3D::Create({ false,true }, { mapDispTex_ }));

	// ------- モデル ------- //

	cubeMod_.reset(Model::Create());
	skydomeMod_.reset(Model::Load({ "skydome/", "skydome.obj", false, }));

	buildingMod_.reset(Model::Load({ "building/", "building.obj", false, }));
	barrierMod_.reset(Model::Load({ "barrier/", "barrier.obj", false, }));

	// ------- マップ ------- //

	mapMan_.Load({ { cubeMod_.get() }, { mapDispSpr_.get() } });

	// ----- 静的初期化 ----- //

	Character::StaticInitialize({ mapMan_.CurrentMapPointer(), &particleMan_ });
	Player::StaticIntialize({ barrierMod_.get(), plainTex_});
	FireSpark::StaticInitialize({ cubeMod_.get() });
}
#pragma endregion


#pragma region 初期化
void DemoScene::Initialize()
{
	// マップ初期化
	mapMan_.Initialize({ 0, {}, { 10.0f, 10.0f, 10.0f } });

	// プレイヤー
	player_.Initialize({ {+100,-100,0}, YMath::AdjustAngle({0,0,1}), {10.0f,10.0f,10.0f} });

	color_.reset(Color::Create());
	fcolor_.reset(Color::Create({ 0.1f,0.25f,1.0f,0.25f }));

	filter_.reset(ObjectSprite3D::Create({ {240,-120,0},{},{120.0f,80.0f,1.0f} }));

	Vector2 sizeHalf = mapMan_.CurrentMapPointer()->Size();
	center_ = { sizeHalf.x_, -sizeHalf.y_, 0.0f };

	buildings_[0].reset(ObjectModel::Create({ center_ + Vector3(-100.0f, -120.0f, +120.0f), {}, Vector3(15.0f,15.0f,15.0f) * 2.0f }));
	buildings_[1].reset(ObjectModel::Create({ center_ + Vector3(- 60.0f, -120.0f, +100.0f), {}, Vector3(20.0f,20.0f,20.0f) * 2.0f }));
	buildings_[2].reset(ObjectModel::Create({ center_ + Vector3(- 40.0f, -120.0f, +100.0f), {}, Vector3(15.0f,15.0f,15.0f) * 2.0f }));
	buildings_[3].reset(ObjectModel::Create({ center_ + Vector3(- 20.0f, -120.0f, + 80.0f), {}, Vector3(10.0f,10.0f,10.0f) * 2.0f }));
	buildings_[4].reset(ObjectModel::Create({ center_ + Vector3(- 10.0f, -120.0f, +140.0f), {}, Vector3(10.0f,10.0f,10.0f) * 2.0f }));
	buildings_[5].reset(ObjectModel::Create({ center_ + Vector3(+ 20.0f, -120.0f, +120.0f), {}, Vector3(25.0f,25.0f,25.0f) * 2.0f }));
	buildings_[6].reset(ObjectModel::Create({ center_ + Vector3(+ 60.0f, -120.0f, + 80.0f), {}, Vector3(15.0f,15.0f,15.0f) * 2.0f }));
	buildings_[7].reset(ObjectModel::Create({ center_ + Vector3(+120.0f, -120.0f, +140.0f), {}, Vector3(10.0f,10.0f,10.0f) * 2.0f }));
	buildingColor_.reset(Color::Create({ 1.0f,1.0f,1.0f,1.0f }));


	// 天球初期化
	skydome_.Initialize({ center_, {}, {600.0f,600.0f,600.0f} }, skydomeMod_.get());

	// カメラ初期化
	cameraMan_.Initialize(&center_);

	// ライト初期化
	lightGroup_.reset(LightGroup::Create());
	{
		lightGroup_->SetDirectionalLightActive(0, false);
		lightGroup_->SetDirectionalLightDirection(0, { +1.0f,-1.0f, 0.0f });
		lightGroup_->SetDirectionalLightColor(0, { 1.0f,1.0f,1.0f });

		lightGroup_->SetDirectionalLightActive(1, false);
		lightGroup_->SetDirectionalLightDirection(1, { +0.5f,+0.1f,+0.2f });
		lightGroup_->SetDirectionalLightColor(1, { 1.0f,1.0f,1.0f });

		lightGroup_->SetDirectionalLightActive(2, false);
		lightGroup_->SetDirectionalLightDirection(2, { -0.5f,+0.1f,-0.2f });
		lightGroup_->SetDirectionalLightColor(2, { 1.0f,1.0f,1.0f });
	}
	{
		lightGroup_->SetPointLightActive(0, true);
		lightGroup_->SetPointLightPos(0, center_ + Vector3(-60.0f, -80.0f, -40.0f));
		lightGroup_->SetPointLightAtten(0, { 0.0001f,0.0001f,0.0001f });
		lightGroup_->SetPointLightColor(0, { 0.75f,0.25f,0.25f });

		lightGroup_->SetPointLightActive(1, true);
		lightGroup_->SetPointLightPos(1, center_ + Vector3(-60.0f, -80.0f, +40.0f));
		lightGroup_->SetPointLightAtten(1, { 0.0001f,0.0001f,0.0001f });
		lightGroup_->SetPointLightColor(1, { 0.75f,0.25f,0.25f });

		lightGroup_->SetPointLightActive(2, true);
		lightGroup_->SetPointLightPos(2, center_ + Vector3(-140.0f, -80.0f, -20.0f));
		lightGroup_->SetPointLightAtten(2, { 0.0001f,0.0001f,0.0001f });
		lightGroup_->SetPointLightColor(2, { 0.75f,0.25f,0.25f });
	}

	lightGroup2_.reset(LightGroup::Create());
	{
		lightGroup2_->SetDirectionalLightActive(0, true);
		lightGroup2_->SetDirectionalLightDirection(0, { +1.0f,+1.0f, 0.0f });
		lightGroup2_->SetDirectionalLightColor(0, { 1.00f,1.00f,1.00f });

		lightGroup2_->SetDirectionalLightActive(1, true);
		lightGroup2_->SetDirectionalLightDirection(1, { -1.0f,+1.0f,+1.0f });
		lightGroup2_->SetDirectionalLightColor(1, { 1.00f,1.00f,1.00f });

		lightGroup2_->SetDirectionalLightActive(2, true);
		lightGroup2_->SetDirectionalLightDirection(2, { +1.0f,+1.0f,+1.0f });
		lightGroup2_->SetDirectionalLightColor(2, { 1.00f,1.00f,1.00f });
	}
	{
		lightGroup2_->SetPointLightActive(0, true);
		lightGroup2_->SetPointLightPos(0, {});
		lightGroup2_->SetPointLightAtten(0, { 0.0025f,0.0025f,0.0025f });
		lightGroup2_->SetPointLightColor(0, { 0.25f,0.75f,0.75f });

		lightGroup2_->SetPointLightActive(1, true);
		lightGroup2_->SetPointLightPos(1, {});
		lightGroup2_->SetPointLightAtten(1, { 0.0025f,0.0025f,0.0025f });
		lightGroup2_->SetPointLightColor(1, { 0.25f,0.75f,0.75f });

		lightGroup2_->SetPointLightActive(2, true);
		lightGroup2_->SetPointLightPos(2, {});
		lightGroup2_->SetPointLightAtten(2, { 0.0025f,0.0025f,0.0025f });
		lightGroup2_->SetPointLightColor(2, { 0.25f,0.75f,0.75f });
	}

	// ビュープロジェクション初期化
	vp_.Initialize({});

	// アタリ判定マネージャー初期化
	collMan_.Initialize();

	// パーティクルマネージャー初期化
	particleMan_.Initialize();
}
#pragma endregion

#pragma region 終了処理
void DemoScene::Finalize()
{
	lightGroup_.reset();
}
#pragma endregion

#pragma region 更新
void DemoScene::Update()
{
	// ホットリロード
	if (sKeys_->IsTrigger(DIK_L))
	{
		mapMan_.Load({ { cubeMod_.get() }, { mapDispSpr_.get() } });
		mapMan_.Reset();
	}

	// リセット
	if (sKeys_->IsTrigger(DIK_R))
	{
		collMan_.Initialize();
	}

	// 次のシーンへ
	if (sKeys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("RESULT");
	}

	// プレイヤー
	player_.Update();

	for (size_t i = 0; i < buildings_.size(); i++)
	{
		buildings_[i]->UpdateMatrix();
	}

	if (isA)
	{
		filter_->pos_.x_ += 3.0f * sKeys_->Horizontal();
		filter_->pos_.y_ += 3.0f * sKeys_->Vertical();
	}
	filter_->UpdateMatrix();

	// マップマネージャー
	mapMan_.Update();

	// カメラ
	cameraMan_.Update();

	// ビュープロジェクション
	vp_ = cameraMan_.GetViewProjection();
	vp_.Update();

	// パーティクルマネージャー
	particleMan_.Update();

	// スカイドーム
	skydome_.Update();

	// アタリ判定マネージャー
	collMan_.Update();
}
#pragma endregion


#pragma region 描画
void DemoScene::DrawBackSprite2Ds()
{

}

void DemoScene::DrawBackSprite3Ds()
{
}

void DemoScene::DrawModels()
{
	// 天球
	skydome_.Draw(vp_, lightGroup_.get(), color_.get());

	// ビル
	for (size_t i = 0; i < buildings_.size(); i++)
	{
		buildingMod_->Draw(buildings_[i].get(), vp_, lightGroup_.get(), color_.get());
	}

	// マップチップ
	mapMan_.Draw(vp_, lightGroup_.get(), mapTex_, color_.get());
	
	// プレイヤー
	player_.Draw(vp_, lightGroup2_.get(), buildingColor_.get());


	// パーティクル
	particleMan_.Draw(vp_, lightGroup2_.get());
}

void DemoScene::DrawFrontSprite3Ds()
{
	filterSpr_->Draw(filter_.get(), vp_, fcolor_.get());

}

void DemoScene::DrawFrontSprite2Ds()
{
	// マップチップ
	//mapMan_.Draw2D();
}

void DemoScene::Draw()
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