#include "GameScene.h"
#include "YMath.h"
#include "CalcTransform.h"
#include "Def.h"
#include <cassert>

#pragma region 名前空間宣言

using namespace DX;
using namespace Input;
using namespace Math;
using namespace Game;

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

	plainT_ = pTexManager_->Load("white1x1.png", false);

	playerT_ = pTexManager_->Load("player.png", true);
	enemyT_ = pTexManager_->Load("enemy.png", true);

	// ----- オーディオ ----- //

	aA_ = pAudioManager_->Load("Resources/Audios/fanfare.wav");

	// ----- モデル ----- //

	cubeM_.reset(Model::Create());
	skydomeM_.reset(Model::Load("skydome"));

	// ----- スプライト ----- //

	quadS_.reset(Sprite::Create({ { 64,64 } }, { playerT_ }));
	curtenS_.reset(Sprite::Create({ WinSize }, { plainT_ }));

	// ----- マップ ----- //

	map_.Load("stage1.csv");
	map_.Initialize({ 5.0f, { 0.0f,+30.0f,-30.0f }, cubeM_.get(), plainT_ });

	// ----- 静的初期化 ----- //

	Transition::Blackout::StaticInitialize({ curtenS_.get() });
	Player::StaticIntialize({ cubeM_.get(), playerT_ });

}
#pragma endregion


#pragma region 初期化
void GameScene::Initialize()
{
	// 乱数初期化
	Srand();

	// 床初期化
	const size_t s = 8;
	for (size_t i = 0; i < s; i++)
	{
		std::vector<Object> fs;
		for (size_t j = 0; j < s; j++)
		{
			Object f;
			f.Initialize({});
			f.scale_ = { 20,1,20 };
			f.pos_ =
			{
				((f.scale_.x_ * 2.0f) * j) - ((s - 1) * (f.scale_.x_)),
				-f.scale_.y_,
				((f.scale_.z_ * 2.0f) * i) - ((s - 1) * (f.scale_.z_))
			};
			float c = 1.0f - (((i + j) % 2 == 0) * 0.5f);
			f.color_= { c,c,c,1.0f };
			f.Update();
			fs.push_back(f);
		}
		floor.push_back(fs);
	}

	sprite_.Initialize({ });

	// プレイヤー初期化
	player_ = std::make_unique<Player>();
	player_->Initialize();

	// エネミー初期化
	enemy_.Initialize({ {0,5.0f,20.0f},{},{5.0f,5.0f,5.0f} });
	enemy_.rota_ = AdjustAngle(Vec3(0, 0, -1));

	// 天球初期化
	skydome_.Initialize(skydomeM_.get());

	// カメラ初期化
	camera_.Initialize({ {150.0f, 50.0f, -50.0f}, {PI / 16.0f, -PI / 3.0f, 0.0f} });

	// ビュープロジェクション初期化
	vp_.Initialize({});

	sceneMan_.Initialize();
	collMan_.Initialize();
}
#pragma endregion


#pragma region 更新
void GameScene::Update()
{
	// ホットリロード
	if (keys_->IsTrigger(DIK_L))
	{
		map_.Load("stage1.csv");
		map_.Reset({ 0.0f,+30.0f,-30.0f });
	}

	// リセット
	if (keys_->IsTrigger(DIK_R))
	{
		// プレイヤー
		player_->Reset();
		// エネミー
		enemy_.rota_  = AdjustAngle(Vec3(0, 0, -1));

		collMan_.Initialize();
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
	
	// プレイヤー
	if (keys_->IsTrigger(DIK_W)) { player_->Jump(); }
	if (keys_->IsTrigger(DIK_SPACE)) { player_->Attack(); }
	player_->Update();
	
	// エネミー
	enemy_.pos_.x_ += keys_->Horizontal(Keys::MoveStandard::Arrow) * 0.2f;
	enemy_.pos_.z_ += -keys_->Vertical(Keys::MoveStandard::Arrow) * 0.2f;

	enemy_.Update();

	// スカイドーム
	skydome_.Update();

	// マップマネージャー
	map_.Update();

	// カメラ
	camera_.Update();

	// ビュープロジェクション
	vp_ = camera_.GetViewProjection();
	vp_.Update();

	// シーンマネージャー
	if (keys_->IsTrigger(DIK_1)){ sceneMan_.Change(Scene::PLAY); }
	sceneMan_.Update();
}
#pragma endregion


#pragma region 描画
void GameScene::DrawBackSprites()
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

	quadS_->Draw(sprite_);
}

void GameScene::DrawModels()
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

	//skydome_.Draw(vp_);

	// map
	map_.Draw(vp_);

	// floor
	//for (size_t i = 0; i < floor.size(); i++)
	//{
	//	for (size_t j = 0; j < floor[i].size(); j++)
	//	{
	//		cubeM_->Draw(floor[i][j], vp_);
	//	}
	//}

	// player
	player_->Draw(vp_);
	// enemy
	cubeM_->Draw(enemy_, vp_, enemyT_);
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

	quadS_->Draw(sprite_);
	sceneMan_.Draw();
}

void GameScene::Draw()
{
	// -------------------------- //
	Sprite::StaticSetDrawCommand();
	// ----- 背景スプライト ----- //

	DrawBackSprites();

	// -------------------------- //
	Model::StaticSetDrawCommand();
	// --------- モデル --------- //

	DrawModels();

	// -------------------------- //
	Sprite::StaticSetDrawCommand();
	// ----- 前景スプライト ----- //

	DrawFrontSprites();
	
	// -------------------------- //
}
#pragma endregion