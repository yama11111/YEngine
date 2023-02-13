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
//using namespace YActor;
using namespace YDrawer;
//using namespace YParticle;
//using namespace YTransition;
#pragma endregion 

#pragma region Static関連
#pragma endregion 

#pragma region 読み込み
void PlayScene::Load()
{
	// ----- テクスチャ ----- //

	plainT_		 = pTexManager_->Load("white1x1.png", false);

	playerT_	 = pTexManager_->Load("player.png", true);
	enemyT_		 = pTexManager_->Load("enemy.png", false);

	mapT_		 = pTexManager_->Load("map.png", false);
	mapDispT_	 = pTexManager_->Load("mapDisp.png", false);

	// ----- オーディオ ----- //

	//aA_ = pAudioManager_->Load("Resources/Audios/fanfare.wav");

	// ----- スプライト (2D) ----- //

	windowS_.reset(Sprite2D::Create({ WinSize }, { plainT_ }));
	curtenS_.reset(Sprite2D::Create({ WinSize }, { plainT_ }));
	mapDispS_.reset(Sprite2D::Create({ {32,32} }, { mapDispT_ }));

	// ----- スプライト (3D) ----- //

	//debriB_.reset(Sprite3D::Create(false));
	
	// ------- モデル ------- //

	cubeM_.reset(Model::Create());
	skydomeM_.reset(Model::Load({ "skydome/", "skydome.obj", false, }));
	slimeM_.reset(Model::Load({ "slime/", "slime.obj", false, }));

	zundamonM_.reset(Model::Load({ "zundamon/", "zundamon.pmx", false, }));


	sphereMod_.reset(Model::LoadObj("sphere", true));
	groundMod_.reset(Model::LoadObj("ground", false));
	triangleMod_.reset(Model::LoadObj("triangle", false));

	// ------- マップ ------- //

	mapMan_.Load({ cubeM_.get(), mapT_, mapDispS_.get() });

	// ----- 静的初期化 ----- //

	//Floor::StaticIntialize({ cubeM_.get(), plainT_ });

	//Character::SetMapChipPointer({ mapMan_.CurrentMapPointer(), &particleMan_ });

	//ParticleManager::StaticInitialize({ cubeM_.get()});
	PlayerDrawerCommon::StaticInitialize({});
}
#pragma endregion


#pragma region 初期化
void PlayScene::Initialize()
{
	// プレイヤー
	player_.reset(ObjectModel::Create({ {+20,0,0}, YMath::AdjustAngle({0,0,1}), {10.0f,10.0f,10.0f} }));
	playerDra_.Initialize(&player_->m_);

	float plaSca = 5.0f; Vector3 plaNormal = { 1,1,0 };
	planeObj_.reset(ObjectModel::Create({ {},AdjustAngle(plaNormal),{plaSca, plaSca, plaSca}}));
	plane_.SafeSetNormal(plaNormal);
	plane_.distance_ = 0.0f;
	planeColor_.reset(Color::Create({ 0.5f,1.0f,1.0f,0.75f }));

	float raySca = 1.0f; Vector3 rayDirection = { 0,-1,0 };
	rayObj_.reset(ObjectModel::Create({ {},AdjustAngle(rayDirection),{raySca * 0.25f, raySca * 0.25f, raySca * 5.0f} }));
	ray_.start_ = Vector3(0, 1, 0);
	ray_.SafeSetDirection(rayDirection);
	rayColor_.reset(Color::Create({ 0.5f,0.5f,1.0f,0.75f }));

	float triSca = 5.0f;
	triangleObj_.reset(ObjectModel::Create({ {-2,2,-1},{},{triSca, triSca, 0.1f}}));
	triangle_.p0_ = Vector3(-triSca,0,-triSca) + triangleObj_->pos_;
	triangle_.p1_ = Vector3(-triSca,0,+triSca) + triangleObj_->pos_;
	triangle_.p2_ = Vector3(+triSca,0,-triSca) + triangleObj_->pos_;
	triangle_.CalcNormal();
	triangleObj_->rota_ = AdjustAngle(triangle_.normal_);
	triangleColor_.reset(Color::Create({ 1.0f,0.5f,1.0f,0.75f }));
	
	float sphSca = 1.0f;
	sphereObj_.reset(ObjectModel::Create({ {0,2,0},{},{sphSca, sphSca, sphSca} }));
	sphere_.center_ = sphereObj_->pos_;
	sphere_.SafeSetRadius(sphSca);
	sphereColor_.reset(Color::Create({ 1.0f,1.0f,0.5f,1.0f }));

	// マップ初期化
	mapMan_.Initialize({ 0, {}, { 25.0f, 7.5f, 7.5f } });

	// 天球初期化
	//skydome_.Initialize(&player_.pos_, skydomeM_.get());

	// カメラ初期化
	cameraMan_.Initialize();
	cameraMan_.SetFollowPoint(&player_->pos_);

	// ライト初期化
	lightGroup_.reset(LightGroup::Create());
	lightGroup_->SetDirectionalLightColor(0, { 1.0f,1.0f,1.0f });
	lightGroup_->SetDirectionalLightColor(1, { 1.0f,1.0f,1.0f });
	lightGroup_->SetDirectionalLightColor(2, { 1.0f,1.0f,1.0f });

	// ビュープロジェクション初期化
	vp_.Initialize({ {0,5,-15} });

	// アタリ判定マネージャー初期化
	collMan_.Initialize();

	// パーティクルマネージャー初期化
	//particleMan_.Initialize();
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
	// ホットリロード
	if (keys_->IsTrigger(DIK_L))
	{
		mapMan_.Load({ cubeM_.get(), mapDispT_, mapDispS_.get() });
		mapMan_.Reset();
	}

	// リセット
	if (keys_->IsTrigger(DIK_R))
	{
		collMan_.Initialize();
	}

	// 次のシーンへ
	if (keys_->IsTrigger(DIK_0))
	{
		SceneManager::GetInstance()->Change("RESULT");
	}

	// プレイヤー
	player_->rota_.y_ += 0.005f;
	player_->UpdateMatrix();
	playerDra_.Update();

	// マップマネージャー
	mapMan_.Update();

	triangleObj_->UpdateMatrix();
	
	ray_.start_.x_ += 0.1f * keys_->Horizontal(Keys::MoveStandard::WASD);
	ray_.start_.y_ += 0.1f * keys_->Vertical(Keys::MoveStandard::WASD);
	ray_.start_.z_ += 0.1f * keys_->Vertical(Keys::MoveStandard::Arrow);
	rayObj_->pos_ = ray_.start_;
	rayObj_->pos_.y_ -= rayObj_->scale_.z_;
	rayObj_->UpdateMatrix();
	
	planeObj_->UpdateMatrix();

	//sphere_.center_.x_ += 0.1f * keys_->Horizontal(Keys::MoveStandard::WASD);
	//sphere_.center_.y_ += 0.1f * keys_->Vertical(Keys::MoveStandard::WASD);
	//sphere_.center_.z_ += 0.1f * keys_->Vertical(Keys::MoveStandard::Arrow);
	sphereObj_->pos_ = sphere_.center_;
	sphereObj_->UpdateMatrix();

	planeColor_->	SetRGBA({ 0.5f, 1.0f, 1.0f, 1.0f });
	rayColor_->		SetRGBA({ 0.5f, 0.5f, 1.0f, 1.0f });
	triangleColor_->SetRGBA({ 1.0f, 0.5f, 1.0f, 1.0f });
	sphereColor_->	SetRGBA({ 1.0f, 1.0f, 0.5f, 1.0f });

	if (YGame::CollisionRayPlane(ray_, plane_))
	{
		rayColor_->		SetRGBA({ 1.0f, 0.5f, 0.0f, 1.0f });
		planeColor_->	SetRGBA({ 1.0f, 0.0f, 0.5f, 1.0f });
	}
	if (YGame::CollisionRayTriangle(ray_, triangle_))
	{
		rayColor_->		SetRGBA({ 1.0f, 0.5f, 0.0f, 1.0f });
		triangleColor_->SetRGBA({ 1.0f, 0.5f, 0.0f, 1.0f });
	}
	if (YGame::CollisionRaySphere(ray_, sphere_))
	{
		rayColor_->		SetRGBA({ 1.0f, 0.5f, 0.0f, 1.0f });
		sphereColor_->	SetRGBA({ 1.0f, 0.5f, 0.5f, 1.0f });
	}
	if (YGame::CollisionPlaneSphere(plane_, sphere_)) 
	{
		planeColor_->	SetRGBA({ 1.0f, 0.0f, 0.5f, 1.0f });
		sphereColor_->	SetRGBA({ 1.0f, 0.5f, 0.5f, 1.0f });
	}
	if (YGame::CollisionTriangleSphere(triangle_, sphere_)) 
	{
		triangleColor_->SetRGBA({ 1.0f, 0.5f, 0.0f, 1.0f });
		sphereColor_->	SetRGBA({ 1.0f, 0.5f, 0.5f, 1.0f });
	}

	// カメラ
	cameraMan_.Update();

	// ビュープロジェクション
	//vp_ = cameraMan_.GetViewProjection();
	vp_.Update();

	// パーティクルマネージャー
	//particleMan_.Update();

	// スカイドーム
	//skydome_.Update();

	// アタリ判定マネージャー
	collMan_.Update();
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
	// 天球
	//skydome_.Draw(vp_, lightGroup_.get());

	// マップチップ
	//mapMan_.Draw(vp_);

	//playerDra_.Draw(vp_, lightGroup_.get());

	// パーティクル
	//particleMan_.Draw(vp_);

	groundMod_->Draw(planeObj_.get(), vp_, lightGroup_.get(), planeColor_.get());

	cubeM_->Draw(rayObj_.get(), vp_, lightGroup_.get(), rayColor_.get(), plainT_);

	//cubeM_->Draw(triangleObj_.get(), vp_, lightGroup_.get(), triangleColor_.get(), plainT_);
	triangleMod_->Draw(triangleObj_.get(), vp_, lightGroup_.get(), triangleColor_.get());

	sphereMod_->Draw(sphereObj_.get(), vp_, lightGroup_.get(), sphereColor_.get());
}

void PlayScene::DrawFrontSprite3Ds()
{

}

void PlayScene::DrawFrontSprite2Ds()
{
	// マップチップ
	//mapMan_.Draw2D();
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