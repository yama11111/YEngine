#include "PlayScene.h"
#include "SceneManager.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "Player.h"
#include "Slime.h"
#include "Coin.h"

#include "ScoreManager.h"
#include "StageManager.h"
#include "ParticleManager.h"
#include "CircleShadowManager.h"

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
	
	// プレイヤー
	Player::StaticInitialize(&camera_);
}
#pragma endregion


#pragma region 初期化
void PlayScene::Initialize()
{
	StageManager::GetInstance()->Reset();

	CircleShadowManager::GetInstance()->Intialize();

	// ゲームキャラクターマネージャー初期化
	pObjectMan_->Initialize(&transferVP_);

	// カメラ初期化
	camera_.Initialize();

	// ビュープロジェクション初期化
	transferVP_.Initialize();
	
	uint32_t stageIndex = StageManager::GetInstance()->CurrentStageIndex();
	if (stageIndex == 0)
	{
		pLevel_ = Level::LoadJson("levelData.json");
	}
	else if (stageIndex == 1)
	{
		pLevel_ = Level::LoadJson("levelData_2.json");
	}

	pScoreManager_ = ScoreManager::GetInstance();
	pScoreManager_->Initialize();

	// UI
	uiDra_.Initialize();

	// 開始演出描画クラス
	beginingDra_.Initialize();
	beginingDra_.PlayAnimation();

	isStart_ = false;

	isStop_ = false;

	pause_.Initialize();

	ScoreManager::GetInstance()->Initialize();
	ScoreManager::GetInstance()->StartScoreMeasurement();


	cbDiscardColor_.reset(ConstBufferObject<CBDiscardColor>::Create());
	
	pWorldPE_ = PostEffect::Create({ "Texture0" });
	worldPEObj_.reset(DrawObjectForPostEffect::Create(Transform::Status::Default(), pWorldPE_));
	worldPEObj_->InsertConstBuffer(cbDiscardColor_.get());

	pFeverPE_ = PostEffect::Create({ "Texture0" });
	feverPEObj_.reset(DrawObjectForPostEffect::Create(Transform::Status::Default(), pFeverPE_));
	feverPEObj_->InsertConstBuffer(cbDiscardColor_.get());
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
			isStart_ = true;
		}

		uiDra_.Update();

		CircleShadowManager::GetInstance()->Reset();

		// 開始演出中更新しない
		pObjectMan_->Update(isStart_);

		camera_.Update();
		transferVP_ = camera_.GetViewProjection();

		ParticleManager::GetInstance()->Update();
	}
	
	feverPEObj_->Update();
	worldPEObj_->Update();
	
	ImGui::Begin("Discard");
	ImGui::InputFloat("R", &cbDiscardColor_->data_.discardColor.x);
	ImGui::InputFloat("G", &cbDiscardColor_->data_.discardColor.y);
	ImGui::InputFloat("B", &cbDiscardColor_->data_.discardColor.z);
	ImGui::InputFloat("threshold", &cbDiscardColor_->data_.threshold);
	ImGui::End();
	
	transferVP_.UpdateMatrix();

	pObjectMan_->DrawDebugText();
	camera_.DrawDebugText();

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
	{
		std::vector<PostEffect*> pes = { pFeverPE_ };
		PipelineManager::GetInstance()->RenderToPostEffect(pes);
	}

	pObjectMan_->Draw();

	{
		std::vector<PostEffect*> pes = { pWorldPE_ };
		PipelineManager::GetInstance()->RenderToPostEffect(pes);
	}

	feverPEObj_->Draw("World_Fever", 0);
	worldPEObj_->Draw("World_0", 0);
	
	beginingDra_.Draw();
	
	pause_.Draw();
	
	uiDra_.Draw();

	ParticleManager::GetInstance()->Draw();
}
#pragma endregion