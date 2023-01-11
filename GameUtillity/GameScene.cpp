#include "GameScene.h"
#include "MathUtillity.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>

#pragma region 名前空間宣言

using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YTransition;
using namespace YGame;

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

	//playerT_	 = pTexManager_->Load("player.png", true);
	//enemyT_	 = pTexManager_->Load("enemy.png", true);

	playerT_	 = pTexManager_->Load("player.png", true);
	enemyT_		 = pTexManager_->Load("enemy.png", true);

	mapT_		 = pTexManager_->Load("map.png", false);
	mapDispT_	 = pTexManager_->Load("mapDisp.png", false);

	backgroundT_ = pTexManager_->Load("back.png", false);

	debriT_		 = pTexManager_->Load("debri.png", true);

	// ----- オーディオ ----- //

	//aA_ = pAudioManager_->Load("Resources/Audios/fanfare.wav");

	// ----- スプライト ----- //

	windowS_.reset(Sprite::Create({ WinSize }, { plainT_ }));
	curtenS_.reset(Sprite::Create({ WinSize }, { plainT_ }));
	mapDispS_.reset(Sprite::Create({ {32,32} }, { mapDispT_ }));

	// ------- モデル ------- //

	cubeM_.reset(Model::Create());
	//skydomeM_.reset(Model::Load("skydome"));
	skydomeM_.reset(Model::Load({ "skydome/", "skydome.obj", false, false  }));

	// ----- ビルボード ----- //

	debriB_.reset(Billboard::Create(false));

	// ------- マップ ------- //

	mapMan_.Load({ cubeM_.get(), mapT_, mapDispS_.get() });

	// ----- 静的初期化 ----- //

	Blackout::StaticInitialize({ curtenS_.get() });
	Floor::StaticIntialize({ cubeM_.get(), plainT_ });

	Character::SetMapChipPointer(mapMan_.CurrentMapPointer());

	Player::StaticIntialize({ cubeM_.get(), playerT_ });
	Slime::StaticIntialize({ cubeM_.get(), enemyT_ });
}
#pragma endregion


#pragma region 初期化
void GameScene::Initialize()
{
	// 乱数初期化
	Srand();

	// マップ初期化
	mapMan_.Initialize({ 0, {}, { 7.5f, 7.5f, 7.5f } });

	// プレイヤー初期化
	player_ = std::make_unique<Player>();
	player_->Initialize({ {0.0f, 80.0f, 50.0f} });

	 // エネミー初期化
	enemy_ = std::make_unique<Slime>();
	enemy_->Initialize({ {0.0f, 80.0f, 175.0f} });

	// 背景初期化
	background_.Initialize({});

	// 天球初期化
	skydome_.Initialize(skydomeM_.get());

	// カメラ初期化
	cameraMan_.SetFollowPoint(player_->PosPointer());
	cameraMan_.Initialize();

	// ビュープロジェクション初期化
	vp_.Initialize({});

	// アタリ判定マネージャー初期化
	collMan_.Initialize();

	// シーンマネージャー初期化
	sceneMan_.Initialize();
	
#pragma region Team
		blocks_.resize(num_);
		moves_.resize(num_);
		scales_.resize(num_);
		times_.resize(num_);
		float scale = 2.0f;
		for (size_t i = 0; i < num_; i++)
		{
			blocks_[i].Initialize({ {}, {}, {scale,scale,scale} }, { 0.5f,0.5f,1.0f,0.5f });
			
			moves_[i].Initialize({}, { scale * 2.0f * i, 0.0f, 0.0f }, 2.0f);

			std::vector<Vec3> scales;
			scales.push_back({});
			scales.push_back({ 1,1,1 });
			for (size_t j = 0; j < i + 1; j++)
			{
				float s = 0.5f * (float)j;
				scales.push_back({s,s,s});
			}
			scales.push_back({});
			scales_[i].Initialize(scales, 2.0f);

			times_[i].Initialize(time);
		}

		timer2_.Initialize(time2);
		block_.Initialize({ {0.0f,scale * 2.0f,0.0f}, {}, {scale,scale,scale} }, { 0.5f,0.5f,1.0f,0.5f });
		debris_.resize(num2_);
		moves2_.resize(num2_);
		rotas2_.resize(num2_);
		scales2_.resize(num2_);
		alphas2_.resize(num2_);
		for (size_t i = 0; i < num2_; i++)
		{
			debris_[i].Initialize({ block_.pos_, {}, {} }, { 0.5f,1.0f,1.0f,0.5f });

			Vec3 m =
			{
				(float)GetRand(-5, 5),
				(float)GetRand(-5, 5),
				(float)GetRand(-5, 5)
			};

			int rNum = static_cast<int>(((PI / 2.0f) * 1000.0f));

			Vec3 r = 
			{
				(float)GetRand(-rNum, rNum) / 1000.0f,
				(float)GetRand(-rNum, rNum) / 1000.0f,
				(float)GetRand(-rNum, rNum) / 1000.0f,
			};

			float s = (float)GetRand(10, 15) / 10.0f;
			std::vector<Vec3> ss;
			ss.push_back({});
			ss.push_back({ s/ 2.0f,s / 2.0f,1.0f });
			ss.push_back({ s,s,1.0f });

			moves2_[i].Initialize({}, m, 2.0f);
			rotas2_[i].Initialize({}, r, 2.0f);
			scales2_[i].Initialize(ss, 2.0f);
			alphas2_[i].Initialize(1.0f, 0.0f, 2.0f);

			isBreak_ = false;
		}
#pragma endregion
	
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
		// プレイヤー
		player_->Reset({ {0.0f, 80.0f, 25.0f} });
		// エネミー
		enemy_->Reset({ {0.0f, 80.0f, 175.0f} });

		collMan_.Initialize();

#pragma region Team
		for (size_t i = 0; i < times_.size(); i++)
		{
			times_[i].Initialize(time);
		}
		timer2_.Initialize(time2);
		isBreak_ = false;
#pragma endregion

	}

	if (sceneMan_.GetScene() == Scene::TITLE)
	{

	}
	else if (sceneMan_.GetScene() == Scene::TUTORIAL)
	{

	}
	else if (sceneMan_.GetScene() == Scene::PLAY)
	{

	}
	else if (sceneMan_.GetScene() == Scene::PAUSE)
	{

	}
	else if (sceneMan_.GetScene() == Scene::CLEAR)
	{

	}
	else if (sceneMan_.GetScene() == Scene::OVER)
	{

	}

	// マップマネージャー
	mapMan_.Update();

	// プレイヤー
	if (keys_->IsTrigger(DIK_SPACE)) { player_->Jump(); }
	if (keys_->IsTrigger(DIK_RETURN)) { player_->Attack(); }

	player_->SpeedRef().z_ = keys_->Horizontal(Keys::MoveStandard::WASD) * 3.0f;
	//player_->SpeedRef().y_ = -keys_->Vertical(Keys::MoveStandard::WASD) * 3.0f;

	player_->Update();

	collMan_.PushBack(player_.get());

	// エネミー
	
	//enemy_.pos_.z_ += +keys_->Horizontal(Keys::MoveStandard::Arrow) * 0.2f;
	//enemy_.pos_.y_ += -keys_->Vertical(Keys::MoveStandard::Arrow) * 0.2f;

	enemy_->Update();

	collMan_.PushBack(enemy_.get());

	// スカイドーム
	skydome_.Update();

	// カメラ
	//camera_.pos_.x_ += +keys_->Horizontal(Keys::MoveStandard::Arrow) * 0.8f;
	//camera_.pos_.y_ += -keys_->Vertical(Keys::MoveStandard::Arrow) * 0.8f;
	//camera_.rota_.y_ += +keys_->Horizontal(Keys::MoveStandard::WASD) * 0.02f;
	//camera_.rota_.x_ += +keys_->Vertical(Keys::MoveStandard::WASD) * 0.02f;
	cameraMan_.Update();

	// ビュープロジェクション
	vp_ = cameraMan_.GetViewProjection();
	vp_.Update();

	// シーンマネージャー
	sceneMan_.Update();

	// アタリ判定マネージャー
	collMan_.Update();

#pragma region Team

	if (keys_->IsTrigger(DIK_K))
	{
		cameraMan_.Shaking(10, 1); 
	}

	for (size_t i = 0; i < num_; i++)
	{
		times_[i].Update(keys_->IsDown(DIK_K));
		blocks_[i].UniqueUpdate(
			{
				moves_[i].In(times_[i].Ratio()),
				{},
				scales_[i].In(times_[i].Ratio())
			});
	}

	if (keys_->IsTrigger(DIK_B))
	{
		timer2_.SetActive(true);
		cameraMan_.Shaking(10, 1);
		isBreak_ = true;
	}

	timer2_.Update();
	block_.Update();
	for (size_t i = 0; i < num2_; i++)
	{
		debris_[i].color_.a_ = alphas2_[i].In(timer2_.Ratio());
		debris_[i].UniqueUpdate(
			{
				moves2_[i].In(timer2_.Ratio()),
				rotas2_[i].In(timer2_.Ratio()),
				scales2_[i].In(timer2_.Ratio())
			}
		);
	}
#pragma endregion

}
#pragma endregion


#pragma region 描画
void GameScene::DrawBackSprites()
{
	{
		if (sceneMan_.GetScene() == Scene::TITLE)
		{

		}
		else if (sceneMan_.GetScene() == Scene::TUTORIAL)
		{

		}
		else if (sceneMan_.GetScene() == Scene::PLAY)
		{

		}
		else if (sceneMan_.GetScene() == Scene::PAUSE)
		{

		}
		else if (sceneMan_.GetScene() == Scene::CLEAR)
		{

		}
		else if (sceneMan_.GetScene() == Scene::OVER)
		{

		}
	}

	windowS_->Draw(background_, backgroundT_);
}

void GameScene::DrawModels()
{
	{
		if (sceneMan_.GetScene() == Scene::TITLE)
		{

		}
		else if (sceneMan_.GetScene() == Scene::TUTORIAL)
		{

		}
		else if (sceneMan_.GetScene() == Scene::PLAY)
		{

		}
		else if (sceneMan_.GetScene() == Scene::PAUSE)
		{

		}
		else if (sceneMan_.GetScene() == Scene::CLEAR)
		{

		}
		else if (sceneMan_.GetScene() == Scene::OVER)
		{

		}
	}

	// 天球
	//skydome_.Draw(vp_);

	// player
	player_->Draw(vp_);
	// enemy
	enemy_->Draw(vp_);
	// map
	mapMan_.Draw(vp_);

#pragma region Team

	//for (size_t i = 0; i < blocks_.size(); i++)
	//{
	//	cubeM_->Draw(blocks_[i], vp_, plainT_);
	//}

	//if (isBreak_ == false) { cubeM_->Draw(block_, vp_, plainT_); }

#pragma endregion

}

void GameScene::DrawBillboards()
{
	{
		if (sceneMan_.GetScene() == Scene::TITLE)
		{

		}
		else if (sceneMan_.GetScene() == Scene::TUTORIAL)
		{

		}
		else if (sceneMan_.GetScene() == Scene::PLAY)
		{

		}
		else if (sceneMan_.GetScene() == Scene::PAUSE)
		{

		}
		else if (sceneMan_.GetScene() == Scene::CLEAR)
		{

		}
		else if (sceneMan_.GetScene() == Scene::OVER)
		{

		}
	}
	
#pragma region Team

	//if (timer2_.IsEnd() == false)
	//{
	//	for (size_t i = 0; i < debris_.size(); i++)
	//	{
	//		debriB_->Draw(debris_[i], vp_, debriT_);
	//	}
	//}

#pragma endregion

}

void GameScene::DrawFrontSprites()
{
	if (sceneMan_.GetScene() == Scene::TITLE)
	{

	}
	else if (sceneMan_.GetScene() == Scene::TUTORIAL)
	{

	}
	else if (sceneMan_.GetScene() == Scene::PLAY)
	{

	}
	else if (sceneMan_.GetScene() == Scene::PAUSE)
	{

	}
	else if (sceneMan_.GetScene() == Scene::CLEAR)
	{

	}
	else if (sceneMan_.GetScene() == Scene::OVER)
	{

	}

	// map
	mapMan_.Draw2D();

	// scene
	sceneMan_.Draw();
}

void GameScene::Draw()
{
	// -------------------------- //
	SpriteCommon::StaticSetDrawCommand();
	// ----- 背景スプライト ----- //

	DrawBackSprites();

	// -------------------------- //
	ModelCommon::StaticSetDrawCommand();
	// --------- モデル --------- //

	DrawModels();

	// -------------------------- //
	BillboardCommon::StaticSetDrawCommand();
	// ------- ビルボード ------- //

	DrawBillboards();

	// -------------------------- //
	SpriteCommon::StaticSetDrawCommand();
	// ----- 前景スプライト ----- //

	DrawFrontSprites();
	
	// -------------------------- //
}
#pragma endregion