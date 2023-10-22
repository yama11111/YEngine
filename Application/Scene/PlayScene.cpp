#include "PlayScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "Player.h"
#include "Horse.h"
#include "Slime.h"
#include "Coin.h"
#include "DamageEmitter.h"

#include "StageManager.h"

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

	// 描画クラス
	BaseDrawer::StaticInitialize(&transferVP_);
	
	// プレイヤー
	Player::StaticInitialize(&scrollCamera_);
	
	// ペット
	IPet::StaticInitialize(&scrollCamera_);
}
#pragma endregion


#pragma region 初期化
void PlayScene::Initialize()
{
	StageManager::GetInstance()->Reset();

	pLevel_ = Level::LoadJson("levelData.json");

	// マップチップ初期化
	pMapChipManager_->Initialize(StageManager::GetInstance()->CurrentStageIndex() + 1, Vector3(-17.0f, +10.0f, 0.0f), Vector3(1.0f, 1.0f, 1.0f));

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

		// コイン
		{
			// コイン生成
			Coin* newCoin = new Coin();

			// コイン初期化
			newCoin->Initialize({ {120.0f,20.0f,0.0f}, {}, {20.0f,20.0f,20.0f} });

			// 挿入
			pCharacterMan_->PushBack(newCoin);
		}
	}

	DamageEmitter::Initialize(&transferVP_);

	pScoreManager_ = ScoreManager::GetInstance();
	pScoreManager_->Initialize();

	// UI
	uiDra_.Initialize();

	
	// 開始演出タイマー
	startTimer_.Initialize(120, true);

	// マップの大きさでオフセット値変える
	Vector3 offset = { pMapChipManager_->CurrentMapPointer()->Size().x_, pMapChipManager_->CurrentMapPointer()->Size().y_, 0.0f };
	cameraOffset_.Initialize(offset, {}, 2.0f);

	isStart_ = false;

	isStop_ = false;

	pause_.Initialize();
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
	bool isReset = false;

	ImGui::Begin("Game");
	ImGui::Checkbox("isStop", &isStop_);
	isReset = ImGui::Button("Reset");
	ImGui::End();

	pause_.Update();

	if (isStop_ == false &&
		pause_.IsPause() == false)
	{
		startTimer_.Update();

		// 開始演出終了時
		if (startTimer_.IsEnd() && isStart_ == false)
		{
			uiDra_.PlayStartAnimation();

			isStart_ = true;
		}

		uiDra_.Update();

		pLevel_->Update();

		pMapChipManager_->Update();

		// 開始演出中更新しない
		pCharacterMan_->Update(isStart_);

		DamageEmitter::Update();

		scrollCamera_.Update({ cameraOffset_.InOut(startTimer_.Ratio(), 0.4f) });
		transferVP_ = scrollCamera_.GetViewProjection();
	}
	
	transferVP_.UpdateMatrix();

	pCharacterMan_->DrawDebugText();

	// リセット
	if (isReset || spKeys_->IsTrigger(DIK_R) || spPad_->IsTrigger(PadButton::XIP_DOWN))
	{
		SceneManager::GetInstance()->Transition("PLAY", "WAVE_REV");
	}


	StageManager::GetInstance()->Update();
}
#pragma endregion


#pragma region 描画
void PlayScene::Draw()
{
	pLevel_->Draw();

	pMapChipManager_->Draw();

	pCharacterMan_->Draw();

	DamageEmitter::Draw();

	uiDra_.Draw();

	pause_.Draw();
}
#pragma endregion