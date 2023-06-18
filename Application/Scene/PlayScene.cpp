#include "PlayScene.h"
#include "SceneExecutive.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "Player.h"
#include "Slime.h"

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
	// シングルトン
	pMapChipManager_ = MapChipManager::GetInstance();

	// 描画クラス
	IDrawer::StaticInitialize(&transferVP_);

	// プレイヤー
	Player::StaticInitialize(&scrollCamera_);
}
#pragma endregion


#pragma region 初期化
void PlayScene::Initialize()
{
	// マップチップ初期化
	pMapChipManager_->Initialize(0, Vector3(-17.0f, +10.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f));

	// ゲームキャラクターマネージャー生成 + 初期化
	gameCharacterManager_.reset(new GameCharacterManager());
	gameCharacterManager_->Initialize();

	// カメラ初期化
	scrollCamera_.Initialize(Vector3(-20.0f, +10.0f, -20.0f), nullptr, Vector3());

	// ビュープロジェクション初期化
	transferVP_.Initialize();

	// キャラクター
	{
		// プレイヤー
		{
			// プレイヤー生成
			Player* newPlayer = new Player();

			// プレイヤー初期化
			newPlayer->Initialize({ {}, {}, {1.0f,1.0f,1.0f} });

			// 挿入
			gameCharacterManager_->PushBack(newPlayer);
		}

		// スライム
		{
			// スライム生成
			Slime* newSlime = new Slime();

			// スライム初期化
			newSlime->Initialize({ {10.0f,0.0f,0.0f}, {}, {1.0f,1.0f,1.0f} });

			// 挿入
			gameCharacterManager_->PushBack(newSlime);
		}
	}
}
#pragma endregion


#pragma region 終了処理
void PlayScene::Finalize()
{
}
#pragma endregion


#pragma region 更新
void PlayScene::Update()
{
	// マップチップ更新
	pMapChipManager_->Update();
	
	// ゲームキャラクター更新
	gameCharacterManager_->Update();

	// カメラ更新
	scrollCamera_.Update();

	// ビュープロジェクション代入
	transferVP_ = scrollCamera_.GetViewProjection();

	// ビュープロジェクション更新
	transferVP_.UpdateMatrix();

	// リセット
	if (sKeys_->IsTrigger(DIK_R))
	{
		SceneManager::GetInstance()->Change("PLAY");
	}
}
#pragma endregion


#pragma region 描画
void PlayScene::Draw()
{
	// マップチップ描画
	pMapChipManager_->Draw();

	// ゲームキャラクター描画
	gameCharacterManager_->Draw();
}
#pragma endregion