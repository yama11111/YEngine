#include "SelectScene.h"
#include "SceneManager.h"
#include "MathVector.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>
#include "ViewProjectionManager.h"

#include "StageManager.h"

#pragma region 名前空間宣言

using YGame::SelectScene;
using namespace YInput;
using namespace YGame;
using namespace YMath;

#pragma endregion 

#pragma region Static関連
#pragma endregion 


#pragma region 読み込み
void SelectScene::Load()
{
	StageManager::GetInstance()->Load();
	StageManager::GetInstance()->Initialize();

	ViewProjectionManager::GetInstance()->Insert("World", &transferVP_);

	SelectDrawer::SetViewProjection(&transferVP_);
}
#pragma endregion


#pragma region 初期化
void SelectScene::Initialize()
{
	isStarted_ = false;
	startTimer_.Initialize(30, true);
	selectDra_.Initialize();

	stageIndex_ = static_cast<int32_t>(StageManager::GetInstance()->CurrentStageIndex());

	transferVP_.Initialize();
	camera_.Initialize({ 0.0f,+5.0f,0.0f }, { kPI / 2.0f,0.0f,0.0f });
}
#pragma endregion


#pragma region 終了処理
void SelectScene::Finalize()
{
}
#pragma endregion


#pragma region 更新
void SelectScene::Update()
{
	startTimer_.Update();
	if (startTimer_.IsEnd())
	{
		selectDra_.PopAnimation();
		startTimer_.Reset();

		isStarted_ = true;
	}

	if (isStarted_)
	{
		if (spKeys_->IsTrigger(DIK_LEFT) || spKeys_->IsTrigger(DIK_A) ||
			spKeys_->IsTrigger(DIK_DOWN) || spKeys_->IsTrigger(DIK_S) ||
			spPad_->IsTrigger(PadButton::XIP_LEFT) || spPad_->IsLeft(PadStick::LStick, true)||
			spPad_->IsTrigger(PadButton::XIP_DOWN))
		{
			stageIndex_--;
		}
		if (spKeys_->IsTrigger(DIK_RIGHT) || spKeys_->IsTrigger(DIK_D) ||
			spKeys_->IsTrigger(DIK_UP) || spKeys_->IsTrigger(DIK_W) ||
			spPad_->IsTrigger(PadButton::XIP_RIGHT) || spPad_->IsRight(PadStick::LStick, true) ||
			spPad_->IsTrigger(PadButton::XIP_UP))
		{
			stageIndex_++;
		}

		int32_t stageSize = static_cast<int32_t>(StageManager::GetInstance()->MaxStageNum());

		if (stageIndex_ < 0) { stageIndex_ = stageSize - 1; }
		if (stageSize <= stageIndex_) { stageIndex_ = 0; }

		selectDra_.SetStageIndex(stageIndex_);
	}
	
	selectDra_.Update();

	// ビュープロジェクション更新
	camera_.pos_ = Vector3(0.0f, +5.0f, 0.0f) + selectDra_.FollowPoint();
	camera_.Update();
	transferVP_ = camera_.GetViewProjection();
	transferVP_.UpdateMatrix();

	// SPACE でゲーム開始
	if (spKeys_->IsTrigger(DIK_SPACE) || spPad_->IsTrigger(PadButton::XIP_A))
	{
		SceneManager::GetInstance()->Transition("PLAY", "WAVE");

		StageManager::GetInstance()->SetStageIndex(stageIndex_);
	}

	// ESC でタイトルに戻る
	if (spKeys_->IsTrigger(DIK_ESCAPE) || spPad_->IsTrigger(PadButton::XIP_MENU))
	{
		SceneManager::GetInstance()->Transition("TITLE", "WAVE_REV");
	}
}
#pragma endregion


#pragma region 描画

void SelectScene::Draw()
{
	selectDra_.Draw();
}
#pragma endregion