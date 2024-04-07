#include "TestScene.h"
#include "SceneManager.h"
#include "MathVector.h"
#include "MathUtil.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "Player.h"

#include "WorldManager.h"
#include "ScoreManager.h"
#include "StageStatusManager.h"
#include "ViewProjectionManager.h"
#include "ParticleManager.h"
#include "CircleShadowManager.h"

#pragma region 名前空間宣言

using YGame::TestScene;
using namespace YDX;
using namespace YInput;
using namespace YMath;
using namespace YGame;

#pragma endregion 

#pragma region Static関連
#pragma endregion 


#pragma region 読み込み
void TestScene::Load()
{
}
#pragma endregion


#pragma region 初期化
void TestScene::Initialize()
{
	CircleShadowManager::GetInstance()->Intialize();

	WorldManager::GetInstance()->Initialize(WorldKey::eJourneyKey);

	ScoreManager::GetInstance()->Initialize();
	ScoreManager::GetInstance()->StartScoreMeasurement();

	Level::LoadJson("journey.json", WorldKeyStr(WorldKey::eJourneyKey));

	// UI
	uiDra_.Initialize();

	// 開始演出描画クラス
	beginingDra_.Initialize();
	beginingDra_.PlayAnimation();

	isStart_ = false;

	isStop_ = false;

	pause_.Initialize();
}
#pragma endregion


#pragma region 終了処理
void TestScene::Finalize()
{
}
#pragma endregion


#pragma region 更新
void TestScene::Update()
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
			isStart_ = true;
		}
	}

	uiDra_.Update();

	CircleShadowManager::GetInstance()->Reset();

	// 開始演出中更新しない
	WorldManager::GetInstance()->Update(isStart_ && (isStop_ == false && pause_.IsPause() == false));

	ParticleManager::GetInstance()->Update();

	WorldManager::GetInstance()->DrawDebug();

	// リセット
	if (isReset || spKeys_->IsTrigger(DIK_R))
	{
		SceneManager::GetInstance()->Transition("TEST", "WAVE_REV");
	}
}
#pragma endregion


#pragma region 描画
void TestScene::Draw()
{
	WorldManager::GetInstance()->Draw();

	beginingDra_.Draw();

	pause_.Draw();

	uiDra_.Draw();

	ParticleManager::GetInstance()->Draw();
}
#pragma endregion