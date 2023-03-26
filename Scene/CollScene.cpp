#include "CollScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>
#include "imgui.h"

#pragma region 名前空間宣言
using YScene::CollScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
#pragma endregion 

#pragma region Static関連
#pragma endregion 

#pragma region 読み込み
void CollScene::Load()
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

	sphereMod_.reset(Model::LoadObj("sphere", true));
	groundMod_.reset(Model::LoadObj("ground", false));
	triangleMod_.reset(Model::LoadObj("triangle", false));

	// ----- 静的初期化 ----- //

}
#pragma endregion


#pragma region 初期化
void CollScene::Initialize()
{
	float plaSca = 5.0f; Vector3 plaNormal = { 1,1,0 };
	planeObj_.reset(ModelObject::Create({ {},AdjustAngle(plaNormal),{plaSca, plaSca, plaSca} }));
	plane_.SafeSetNormal(plaNormal);
	plane_.distance_ = 0.0f;
	planeColor_.reset(Color::Create({ 0.5f,1.0f,1.0f,0.75f }));

	float raySca = 1.0f; Vector3 rayDirection = { 0,-1,0 };
	rayObj_.reset(ModelObject::Create({ {},AdjustAngle(rayDirection),{raySca * 0.25f, raySca * 0.25f, raySca * 5.0f} }));
	ray_.start_ = Vector3(0, 1, 0);
	ray_.SafeSetDirection(rayDirection);
	rayColor_.reset(Color::Create({ 0.5f,0.5f,1.0f,0.75f }));

	float triSca = 5.0f;
	triangleObj_.reset(ModelObject::Create({ {-2,2,-1},{},{triSca, triSca, 0.1f} }));
	triangle_.p0_ = Vector3(-triSca, 0, -triSca) + triangleObj_->pos_;
	triangle_.p1_ = Vector3(-triSca, 0, +triSca) + triangleObj_->pos_;
	triangle_.p2_ = Vector3(+triSca, 0, -triSca) + triangleObj_->pos_;
	triangle_.CalcNormal();
	triangleObj_->rota_ = AdjustAngle(triangle_.normal_);
	triangleColor_.reset(Color::Create({ 1.0f,0.5f,1.0f,0.75f }));

	float sphSca = 1.0f;
	sphereObj_.reset(ModelObject::Create({ {0,2,0},{},{sphSca, sphSca, sphSca} }));
	sphere_.center_ = sphereObj_->pos_;
	sphere_.SafeSetRadius(sphSca);
	sphereColor_.reset(Color::Create({ 1.0f,1.0f,0.5f,1.0f }));

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

	// アタリ判定マネージャー初期化
	collMan_.Initialize();
}
#pragma endregion

#pragma region 終了処理
void CollScene::Finalize()
{
	lightGroup_.reset();
}
#pragma endregion

#pragma region 更新
void CollScene::Update()
{
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

	triangleObj_->UpdateMatrix();

	ray_.start_.x_ += 0.1f * sKeys_->Horizontal(Keys::MoveStandard::WASD);
	ray_.start_.y_ += 0.1f * sKeys_->Vertical(Keys::MoveStandard::WASD);
	ray_.start_.z_ += 0.1f * sKeys_->Vertical(Keys::MoveStandard::Arrow);
	rayObj_->pos_ = ray_.start_;
	rayObj_->pos_.y_ -= rayObj_->scale_.z_;
	rayObj_->UpdateMatrix();

	planeObj_->UpdateMatrix();

	//sphere_.center_.x_ += 0.1f * keys_->Horizontal(Keys::MoveStandard::WASD);
	//sphere_.center_.y_ += 0.1f * keys_->Vertical(Keys::MoveStandard::WASD);
	//sphere_.center_.z_ += 0.1f * keys_->Vertical(Keys::MoveStandard::Arrow);
	sphereObj_->pos_ = sphere_.center_;
	sphereObj_->UpdateMatrix();

	planeColor_->SetRGBA({ 0.5f, 1.0f, 1.0f, 1.0f });
	rayColor_->SetRGBA({ 0.5f, 0.5f, 1.0f, 1.0f });
	triangleColor_->SetRGBA({ 1.0f, 0.5f, 1.0f, 1.0f });
	sphereColor_->SetRGBA({ 1.0f, 1.0f, 0.5f, 1.0f });

	if (YGame::CollisionRayPlane(ray_, plane_))
	{
		rayColor_->SetRGBA({ 1.0f, 0.5f, 0.0f, 1.0f });
		planeColor_->SetRGBA({ 1.0f, 0.0f, 0.5f, 1.0f });
	}
	if (YGame::CollisionRayTriangle(ray_, triangle_))
	{
		rayColor_->SetRGBA({ 1.0f, 0.5f, 0.0f, 1.0f });
		triangleColor_->SetRGBA({ 1.0f, 0.5f, 0.0f, 1.0f });
	}
	if (YGame::CollisionRaySphere(ray_, sphere_))
	{
		rayColor_->SetRGBA({ 1.0f, 0.5f, 0.0f, 1.0f });
		sphereColor_->SetRGBA({ 1.0f, 0.5f, 0.5f, 1.0f });
	}
	if (YGame::CollisionPlaneSphere(plane_, sphere_))
	{
		planeColor_->SetRGBA({ 1.0f, 0.0f, 0.5f, 1.0f });
		sphereColor_->SetRGBA({ 1.0f, 0.5f, 0.5f, 1.0f });
	}
	if (YGame::CollisionTriangleSphere(triangle_, sphere_))
	{
		triangleColor_->SetRGBA({ 1.0f, 0.5f, 0.0f, 1.0f });
		sphereColor_->SetRGBA({ 1.0f, 0.5f, 0.5f, 1.0f });
	}

	// ビュープロジェクション
	vp_.UpdateMatrix();

	// アタリ判定マネージャー
	collMan_.Update();
}
#pragma endregion


#pragma region 描画
void CollScene::DrawBackSprite2Ds()
{

}

void CollScene::DrawBackSprite3Ds()
{
}

void CollScene::DrawModels()
{
	groundMod_->Draw(planeObj_.get());

	cubeMod_->Draw(rayObj_.get());

	cubeMod_->Draw(triangleObj_.get());
	triangleMod_->Draw(triangleObj_.get());

	sphereMod_->Draw(sphereObj_.get());
}

void CollScene::DrawFrontSprite3Ds()
{

}

void CollScene::DrawFrontSprite2Ds()
{

}

void CollScene::Draw()
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