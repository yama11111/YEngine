#include "PlayScene.h"
#include "SceneManager.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>

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

	// ------- マップ ------- //

	mapMan_.Load({ cubeM_.get(), mapT_, mapDispS_.get() });

	// ----- 静的初期化 ----- //

	//Floor::StaticIntialize({ cubeM_.get(), plainT_ });

	//Character::SetMapChipPointer({ mapMan_.CurrentMapPointer(), &particleMan_ });

	//ParticleManager::StaticInitialize({ cubeM_.get()});
	PlayerDrawerCommon::StaticInitialize({});


	playerS_.reset(Sprite2D::Create({ {128,128} }, { playerT_ }));
	enemyS_.reset(Sprite2D::Create({ {128,128} }, { enemyT_ }));
}
#pragma endregion


#pragma region 初期化
void PlayScene::Initialize()
{
	// プレイヤー
	player_.reset(ObjectModel::Create({ {+20,0,0}, YMath::AdjustAngle({0,0,1}), {10.0f,10.0f,10.0f} }));
	playerDra_.Initialize(&player_->m_);

	sphere_.center_ = { 0,2,0 };
	sphere_.SafeSetRadius(1.0f);

	plane_.SafeSetNormal({ 0,1,0 });
	plane_.distance_ = 0.0f;

	triangle_.p0_ = { -1.0f,0,-1.0f };
	triangle_.p1_ = { -1.0f,0,+1.0f };
	triangle_.p2_ = { +1.0f,0,-1.0f };
	triangle_.SafeSetNormal({ 0.0f,1.0f,0.0f });

	// マップ初期化
	mapMan_.Initialize({ 0, {}, { 25.0f, 7.5f, 7.5f } });

	// 天球初期化
	//skydome_.Initialize(&player_.pos_, skydomeM_.get());

	// カメラ初期化
	cameraMan_.Initialize();
	cameraMan_.SetFollowPoint(&player_->pos_);

	// ライト初期化
	lightGroup_.reset(LightGroup::Create());

	// ビュープロジェクション初期化
	vp_.Initialize({});

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

	sphere_.center_.x_ += 0.1f * keys_->Horizontal();
	sphere_.center_.y_ += 0.1f * keys_->Vertical();

	YCollision::CollisonPlaneSphere(plane_, sphere_);
	YCollision::CollisionTriangleSphere(triangle_, sphere_);

	// カメラ
	cameraMan_.Update();

	// ビュープロジェクション
	vp_ = cameraMan_.GetViewProjection();
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

void PlayScene::DrawModels()
{
	// 天球
	//skydome_.Draw(vp_, lightGroup_.get());

	// マップチップ
	//mapMan_.Draw(vp_);

	playerDra_.Draw(vp_, lightGroup_.get());

	// パーティクル
	//particleMan_.Draw(vp_);
}

void PlayScene::DrawSprite3Ds()
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