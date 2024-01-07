#include "UIDrawer.h"
#include "DrawObjectForSprite3D.h"
#include "ScoreManager.h"
#include "StageManager.h"
#include "ColorConfig.h"
#include "Def.h"
#include "Keys.h"
#include "Pad.h"

using YGame::UIDrawer;
using YGame::Sprite3D;
using YMath::Vector3;
using YInput::Keys;
using YInput::Pad;

namespace
{
	Sprite3D* pPauseSpr = nullptr;

	YGame::ViewProjection vp;

	const Vector3 kInstPos = { +47.0f,-27.0f,0.0f };
	const Vector3 kInstRota = { 0.0f,+kPI / 6.0f,+kPI / 120.0f };
	const Vector3 kInstScale = { 0.1f,0.1f,0.0f };
	
	const Vector3 kStatusPos = { -40.0f,+28.0f,0.0f };
	const Vector3 kStatusRota = { 0.0f,-kPI / 6.0f,+kPI / 24.0f };
	const Vector3 kStatusScale = { 0.1f,0.1f,0.0f };
	
	const Vector3 kScorePos	 = { +40.0f,+30.0f,0.0f };
	const Vector3 kScoreRota = { 0.0f,+kPI / 6.0f,-kPI / 24.0f };
	const Vector3 kScoreScale = { 10.0f,10.0f,0.0f };

	const Vector3 kPausePos = { -60.0f,-32.0f,0.0f };
	const Vector3 kPauseRota = { 0.0f,-kPI / 6.0f,+kPI / 120.0f };
	const Vector3 kPauseScale = { 8.0f,8.0f,0.0f };

	YGame::ScoreManager* pScoreMan = nullptr;
	YGame::StageManager* pStageMan = nullptr;

	Keys* pKeys = nullptr;
	Pad* pPad = nullptr;

	const std::string kShaderTag = "Sprite3DUI";
}

void UIDrawer::LoadResource()
{
	pPauseSpr = Sprite3D::Create({ {"Texture0", Texture::Load("UI/play/button_pause.png")} });

	vp.Initialize();

	pScoreMan = ScoreManager::GetInstance();
	pStageMan = StageManager::GetInstance();

	pKeys = Keys::GetInstance();
	pPad = Pad::GetInstance();
}

void UIDrawer::Initialize()
{
	letterBox_.reset(new UILetterBox());

	letterBox_->Initialize(WinSize, 96.0f, 96.0f);
	letterBox_->SetColor(YMath::GetColor(2, 38, 32, 255));

	// 操作説明
	{
		Transform::Status instStatus;
		instStatus.pos_ = kInstPos;
		instStatus.rota_ = kInstRota;
		instStatus.scale_ = kInstScale;

		instTrfm_.Initialize(instStatus);
		if(instDra_ == nullptr)
		{
			instDra_.reset(InstructionsDrawer::Create(&instTrfm_.m_, &vp));
		}
	}

	// ステータス
	{
		Transform::Status statusStatus;
		statusStatus.pos_ = kStatusPos;
		statusStatus.rota_ = kStatusRota;
		statusStatus.scale_ = kStatusScale;

		statusTrfm_.Initialize(statusStatus);
		if (statusDra_ == nullptr)
		{
			statusDra_.reset(StatusDrawer::Create(&statusTrfm_.m_, &vp));
		}
	}

	// スコア
	{
		Transform::Status scoreStatus;
		scoreStatus.pos_ = kScorePos;
		scoreStatus.rota_ = kScoreRota;
		scoreStatus.scale_ = kScoreScale;

		scoreTrfm_.Initialize(scoreStatus);
		if (scoreDra_ == nullptr)
		{
			scoreDra_.reset(ScoreDrawer::Create(&scoreTrfm_.m_, &vp));
		}
		
		scoreDra_->SetMissionScore(pStageMan->Status(pStageMan->CurrentStageIndex()).mission);
	}

	// ポーズ
	{
		if (pauseButton_ == nullptr)
		{
			pauseButton_.reset(UIButton::Create(
				DrawObjectForSprite3D::Create(
					{ kPausePos, kPauseRota, kPauseScale }, false, false, &vp, pPauseSpr)));
		}
	}
}

void UIDrawer::Update()
{
	letterBox_->Update();

	instTrfm_.UpdateMatrix();
	instDra_->Update();

	statusTrfm_.UpdateMatrix();
	statusDra_->Update(
		pScoreMan->HP(), 
		pScoreMan->MaxHP(), 
		pScoreMan->SpeedLevel());

	scoreTrfm_.UpdateMatrix();
	scoreDra_->ChangeScoreAnimation(pScoreMan->ScoreInCurrentStage());
	scoreDra_->Update();

	pauseButton_->Update(pKeys->IsDown(DIK_ESCAPE) || pPad->IsDown(YInput::PadButton::XIP_MENU));
}

void UIDrawer::PlayStartAnimation()
{
	letterBox_->Close(40, 3.0f);
}

void UIDrawer::Draw()
{
	//letterBox_->Draw("Sprite2DDefault", 3);
	
	instDra_->Draw();
	statusDra_->Draw();
	scoreDra_->Draw();
	pauseButton_->Draw(kShaderTag, 0);
}
