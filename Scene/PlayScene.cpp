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
	cu_.reset(ObjectModel::Create({ {-20,0,0},{},{10.0f,10.0f,10.0f} }));

	// プレイヤー
	player_.reset(ObjectModel::Create({ {+20,0,0}, YMath::AdjustAngle({0,0,1}), {10.0f,10.0f,10.0f} }));
	playerDra_.Initialize(&player_->m_);

	// マップ初期化
	mapMan_.Initialize({ 0, {}, { 25.0f, 7.5f, 7.5f } });

	// 天球初期化
	//skydome_.Initialize(&player_.pos_, skydomeM_.get());

	// カメラ初期化
	cameraMan_.Initialize();
	cameraMan_.SetFollowPoint(&player_->pos_);

	// ライト初期化
	lightGroup_.reset(LightGroup::Create());
	lightGroup_->SetDirectionalLightColor(0, { 0.0f,1.0f,0.0f });
	lightGroup_->SetDirectionalLightColor(1, { 1.0f,0.0f,0.0f });
	lightGroup_->SetDirectionalLightColor(2, { 0.0f,0.0f,1.0f });
	lightGroup_->SetPointLightColor(0, { 0.0f,1.0f,0.0f });
	lightGroup_->SetPointLightColor(1, { 1.0f,0.0f,0.0f });
	lightGroup_->SetPointLightColor(2, { 0.0f,0.0f,1.0f });
	//lightGroup_->SetSpotLightColor(0, { 1.0f,1.0f,1.0f });
	//lightGroup_->SetSpotLightColor(1, { 1.0f,0.0f,0.0f });
	//lightGroup_->SetSpotLightColor(0, { 0.0f,0.0f,1.0f });
	lightDire1_ = { 0,1,5 };
	lightDire2_ = { 0,1,5 };

	// ビュープロジェクション初期化
	vp_.Initialize({});

	// アタリ判定マネージャー初期化
	collMan_.Initialize();

	// パーティクルマネージャー初期化
	//particleMan_.Initialize();

	p_.reset(ObjectSprite2D::Create({ {0,0,0} }));
	e_.reset(ObjectSprite2D::Create({ {0,0,0} }));
	b_ = false;
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

	if (keys_->IsDown(DIK_W) || keys_->IsDown(DIK_S) || keys_->IsDown(DIK_D) || keys_->IsDown(DIK_A))
	{
		if (keys_->IsDown(DIK_W)) { lightDire1_.y_ += 1.0f; }
		if (keys_->IsDown(DIK_S)) { lightDire1_.y_ -= 1.0f; }
		if (keys_->IsDown(DIK_D)) { lightDire1_.x_ += 1.0f; }
		if (keys_->IsDown(DIK_A)) { lightDire1_.x_ -= 1.0f; }

		lightGroup_->SetDirectionalLightDirection(1,lightDire1_);
	}
	if (keys_->IsDown(DIK_UP) || keys_->IsDown(DIK_DOWN) || keys_->IsDown(DIK_RIGHT) || keys_->IsDown(DIK_LEFT))
	{
		if (keys_->IsDown(DIK_UP))	  { lightDire2_.y_ += 1.0f; }
		if (keys_->IsDown(DIK_DOWN))  { lightDire2_.y_ -= 1.0f; }
		if (keys_->IsDown(DIK_RIGHT)) { lightDire2_.x_ += 1.0f; }
		if (keys_->IsDown(DIK_LEFT))  { lightDire2_.x_ -= 1.0f; }

		lightGroup_->SetDirectionalLightDirection(2, lightDire2_);
	}


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


	if (keys_->IsTrigger(DIK_SPACE)) { b_ = !b_; }
	if (pad_->IsTrigger(PadButton::XIP_A)) { b_ = !b_; }
	if (mouse_->IsTrigger(MouseClick::DIM_LEFT)) { b_ = !b_; }
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

	// map
	//mapMan_.Draw(vp_);

	playerDra_.Draw(vp_, lightGroup_.get());

	cubeM_->Draw(cu_.get(), vp_, lightGroup_.get(), plainT_);
	//particleMan_.Draw(vp_);
}

void PlayScene::DrawSprite3Ds()
{
	
}

void PlayScene::DrawFrontSprite2Ds()
{
	// map
	//mapMan_.Draw2D();

	if (b_) { playerS_->Draw(p_.get()); }
	else { enemyS_->Draw(e_.get()); }
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