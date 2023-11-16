#include "PlayScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "Player.h"
#include "Horse.h"
#include "Slime.h"
#include "Coin.h"

#include "ScoreManager.h"
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
	pObjectMan_ = GameObjectManager::GetInstance();
	
	// 描画クラス
	BaseDrawer::StaticInitialize(&transferVP_);
	
	BaseCharacter::StaticInitialize();
	
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

	// ゲームキャラクターマネージャー初期化
	pObjectMan_->Initialize();

	// カメラ初期化
	scrollCamera_.Initialize(Vector3(-15.0f, +10.0f, -30.0f), nullptr, Vector3());

	// ビュープロジェクション初期化
	transferVP_.Initialize();
	
	pLevel_ = Level::LoadJson("levelData.json");

	pScoreManager_ = ScoreManager::GetInstance();
	pScoreManager_->Initialize();

	// UI
	uiDra_.Initialize();

	// 開始演出描画クラス
	beginingDra_.Initialize();
	beginingDra_.PlayAnimation();
	
	// 開始演出タイマー
	startTimer_.Initialize(120, true);

	isStart_ = false;

	isStop_ = false;

	pause_.Initialize();

	ScoreManager::GetInstance()->Initialize();
	ScoreManager::GetInstance()->StartScoreMeasurement();
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

	if (spKeys_->IsTrigger(DIK_K))
	{
		beginingDra_.PlayAnimation();
	}

	if (isStop_ == false &&
		pause_.IsPause() == false)
	{
		beginingDra_.Update();

		if (beginingDra_.IsAct() == false)
		{
			startTimer_.Update();
		}

		// 開始演出終了時
		if (startTimer_.IsEnd() && isStart_ == false)
		{
			uiDra_.PlayStartAnimation();

			isStart_ = true;
		}

		uiDra_.Update();

		// 開始演出中更新しない
		pObjectMan_->Update(isStart_);

		scrollCamera_.Update({ cameraOffset_.InOut(startTimer_.Ratio(), 0.4f) });
		transferVP_ = scrollCamera_.GetViewProjection();
	}

	transferVP_.UpdateMatrix();

	pObjectMan_->DrawDebugText();

	// リセット
	if (isReset || spKeys_->IsTrigger(DIK_R))
	{
		SceneManager::GetInstance()->Transition("PLAY", "WAVE_REV");
	}

	StageManager::GetInstance()->Update();
}
#pragma endregion


#pragma region 描画
void PlayScene::Draw()
{
	pObjectMan_->Draw();

	uiDra_.Draw();

	beginingDra_.Draw();

	pause_.Draw();
}
#pragma endregion