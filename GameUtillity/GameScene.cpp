#include "GameScene.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>

#pragma region 名前空間宣言

using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;
using namespace YActor;
using namespace YDrawer;
using namespace YParticle;
using namespace YTransition;

#pragma endregion 

#pragma region Static関連

Keys* GameScene::keys_ = nullptr;
Mouse* GameScene::mouse_ = nullptr;
Pad* GameScene::pad_ = nullptr;
TextureManager* GameScene::pTexManager_ = nullptr;
AudioManager* GameScene::pAudioManager_ = nullptr;

void GameScene::StaticInitialize(TextureManager* pTexManager, AudioManager* pAudioManager)
{
	assert(pTexManager);
	assert(pAudioManager);
	pTexManager_ = pTexManager;
	pAudioManager_ = pAudioManager;

	keys_ = Keys::GetInstance();
	mouse_ = Mouse::GetInstance();
	pad_ = Pad::GetInstance();
}

#pragma endregion 

GameScene::GameScene() {}

GameScene::~GameScene() {}

#pragma region 読み込み
void GameScene::Load()
{
	// ----- テクスチャ ----- //

	plainT_		 = pTexManager_->Load("white1x1.png", false);

	playerT_	 = pTexManager_->Load("player.png", true);
	enemyT_		 = pTexManager_->Load("e.png", false);

	mapT_		 = pTexManager_->Load("map.png", false);
	mapDispT_	 = pTexManager_->Load("mapDisp.png", false);

	// ----- オーディオ ----- //

	//aA_ = pAudioManager_->Load("Resources/Audios/fanfare.wav");

	// ----- スプライト ----- //

	windowS_.reset(Sprite2D::Create({ WinSize }, { plainT_ }));
	curtenS_.reset(Sprite2D::Create({ WinSize }, { plainT_ }));
	mapDispS_.reset(Sprite2D::Create({ {32,32} }, { mapDispT_ }));

	// ------- モデル ------- //

	cubeM_.reset(Model::Create());
	skydomeM_.reset(Model::Load({ "skydome/", "skydome.obj", false, }));
	slimeM_.reset(Model::Load({ "slime/", "slime.obj", false, }));

	zundamonM_.reset(Model::Load({ "zundamon/", "zundamon.pmx", false, }));

	// ----- ビルボード ----- //

	//debriB_.reset(Sprite3D::Create(false));

	// ------- マップ ------- //

	mapMan_.Load({ cubeM_.get(), mapT_, mapDispS_.get() });

	// ----- 静的初期化 ----- //

	Blackout::StaticInitialize({ curtenS_.get() });
	Floor::StaticIntialize({ cubeM_.get(), plainT_ });

	Character::SetMapChipPointer({ mapMan_.CurrentMapPointer(), &particleMan_ });

	ParticleManager::StaticInitialize({ cubeM_.get()});
	PlayerDrawerCommon::StaticInitialize({});
}
#pragma endregion


#pragma region 初期化
void GameScene::Initialize()
{
	// 乱数初期化
	Srand();

	// プレイヤー
	//player_.Initialize({ {}, YMath::AdjustAngle({0,0,-1}), {10.0f,10.0f,10.0f} });
	player_.Initialize({ {}, YMath::AdjustAngle({0,0,1}), {10.0f,10.0f,10.0f} });
	playerDra_.Initialize(&player_.m_);

	// マップ初期化
	mapMan_.Initialize({ 0, {}, { 25.0f, 7.5f, 7.5f } });

	// 天球初期化
	skydome_.Initialize(&player_.pos_, skydomeM_.get());

	// カメラ初期化
	cameraMan_.Initialize();
	cameraMan_.SetFollowPoint(&player_.pos_);

	// ビュープロジェクション初期化
	vp_.Initialize({});

	// アタリ判定マネージャー初期化
	collMan_.Initialize();

	// パーティクルマネージャー初期化
	particleMan_.Initialize();

	// シーンマネージャー初期化
	sceneMan_.Initialize();
	
}
#pragma endregion


#pragma region 更新
void GameScene::Update()
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

	// プレイヤー
	player_.rota_.y_ += 0.005f;
	player_.UpdateMatrix();
	playerDra_.Update();

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

	// シーンマネージャー
	sceneMan_.Update();

	// アタリ判定マネージャー
	collMan_.Update();

}
#pragma endregion


#pragma region 描画
void GameScene::DrawBackSprite2Ds()
{
	
}

void GameScene::DrawModels()
{
	// 天球
	//skydome_.Draw(vp_);

	// map
	//mapMan_.Draw(vp_);

	playerDra_.Draw(vp_);

	particleMan_.Draw(vp_);
}

void GameScene::DrawSprite3Ds()
{
	
}

void GameScene::DrawFrontSprite2Ds()
{
	// map
	//mapMan_.Draw2D();

	// scene
	//sceneMan_.Draw();
}

void GameScene::Draw()
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