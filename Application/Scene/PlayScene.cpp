#include "PlayScene.h"
#include "SceneExecutive.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "Player.h"
#include "Horse.h"
#include "Slime.h"

#include "DefaultDrawer.h"
#include "PlayerDrawer.h"
#include "HorseDrawer.h"
#include "SlimeDrawer.h"
#include "SlashAttackDrawer.h"
#include "SnortAttackDrawer.h"
#include "BlockDrawer.h"
#include "GoalDrawer.h"
#include "CloudDrawer.h"
#include "SkydomeDrawer.h"

#pragma region 名前空間宣言

using YGame::PlayScene;
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
	pCharacterMan_ = CharacterManager::GetInstance();
	
	pMapChipManager_ = MapChipManager::GetInstance();
	pMapChipManager_->Load("demo.csv");

	// 描画クラス
	{
		BaseDrawer::StaticInitialize(&transferVP_);

		DefaultDrawer::StaticInitialize();

		PlayerDrawer::StaticInitialize();
		
		HorseDrawer::StaticInitialize();

		SlimeDrawer::StaticInitialize();
		
		SlashAttackDrawer::StaticInitialize();
		
		SnortAttackDrawer::StaticInitialize();

		BlockDrawer::StaticInitialize();

		GoalDrawer::StaticInitialize();

		SkydomeDrawer::StaticInitialize();

		CloudDrawer::StaticInitialize();
	}

	// プレイヤー
	Player::StaticInitialize(&scrollCamera_);
	
	// ペット
	IPet::StaticInitialize(&scrollCamera_);
}
#pragma endregion


#pragma region 初期化
void PlayScene::Initialize()
{
	pLevel_ = Level::LoadJson("levelData.json");

	// マップチップ初期化
	pMapChipManager_->Initialize(0, Vector3(-17.0f, +10.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f));

	// ゲームキャラクターマネージャー初期化
	pCharacterMan_->Initialize();

	// カメラ初期化
	scrollCamera_.Initialize(Vector3(-15.0f, +10.0f, -30.0f), nullptr, Vector3());

	// ビュープロジェクション初期化
	transferVP_.Initialize();

	// キャラクター
	{
		// プレイヤー
		{
			// プレイヤー生成
			Player* newPlayer = new Player();
			
			// ペット(ウマ)生成
			Horse* newHorse = new Horse();

			// ペット初期化
			newHorse->Initialize({ {}, {}, {1.0f,1.0f,1.0f} });

			// プレイヤー初期化
			newPlayer->Initialize(
				{ {-100.0f,-100.0f,-100.0f}, {}, {1.0f,1.0f,1.0f} },
				newHorse
			);

			// 挿入
			pCharacterMan_->PushBack(newHorse);
			pCharacterMan_->PushBack(newPlayer);
		}

		// スライム
		{
			// スライム生成
			Slime* newSlime = new Slime();

			// スライム初期化
			newSlime->Initialize({ {10.0f,0.0f,0.0f}, {}, {1.0f,1.0f,1.0f} });

			// 挿入
			pCharacterMan_->PushBack(newSlime);
		}

		// スライム
		{
			// スライム生成
			Slime* newSlime = new Slime();

			// スライム初期化
			newSlime->Initialize({ {40.0f,0.0f,0.0f}, {}, {1.0f,1.0f,1.0f} });

			// 挿入
			pCharacterMan_->PushBack(newSlime);
		}

		// スライム
		{
			// スライム生成
			Slime* newSlime = new Slime();

			// スライム初期化
			newSlime->Initialize({ {80.0f,0.0f,0.0f}, {}, {1.0f,1.0f,1.0f} });

			// 挿入
			pCharacterMan_->PushBack(newSlime);
		}

		// スライム
		{
			// スライム生成
			Slime* newSlime = new Slime();

			// スライム初期化
			newSlime->Initialize({ {120.0f,20.0f,0.0f}, {}, {1.0f,1.0f,1.0f} });

			// 挿入
			pCharacterMan_->PushBack(newSlime);
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
	pLevel_->Update();

	pMapChipManager_->Update();
	
	pCharacterMan_->Update();

	scrollCamera_.Update();
	transferVP_ = scrollCamera_.GetViewProjection();
	transferVP_.UpdateMatrix();

	pCharacterMan_->DrawDebugText();
	
	// リセット
	if (spKeys_->IsTrigger(DIK_R) || spPad_->IsTrigger(PadButton::XIP_MENU))
	{
		SceneManager::GetInstance()->Change("PLAY");
	}
}
#pragma endregion


#pragma region 描画
void PlayScene::Draw()
{
	pLevel_->Draw();

	pMapChipManager_->Draw();

	pCharacterMan_->Draw();
}
#pragma endregion