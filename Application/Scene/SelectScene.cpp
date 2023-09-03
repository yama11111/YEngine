#include "SelectScene.h"
#include "SceneExecutive.h"
#include "MathVector.h"
#include "Def.h"
#include <cassert>
#include <imgui.h>

#include "BlockDrawer.h"
#include "SkydomeDrawer.h"

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
	pLogoSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("select/stage_logo.png")} });
	
	pStickSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("UI/key/stick_L.png")} });

	pButtonSpr_ = Sprite2D::Create({ { "Texture0", Texture::Load("UI/key/button_A.png")} });


	BaseDrawer::StaticInitialize(&transferVP_);

	BlockDrawer::StaticInitialize();

	SkydomeDrawer::StaticInitialize();
}
#pragma endregion


#pragma region 初期化
void SelectScene::Initialize()
{
	pLevel_ = Level::LoadJson("levelData.json");
	
	// ウィンドウサイズ を 3次元ベクトルにしておく
	Vector3 win = ConvertToVector3(WinSize);


	Vector3 logoPos = (win / 2.0f) - Vector3(288.0f, 288.0f, 0.0f);
	logoObj_.reset(DrawObjectForSprite2D::Create({ logoPos, {}, {1.0f,1.0f,1.0f} }, pLogoSpr_));

	Vector3 stickPos = (win / 2.0f) + Vector3(288.0f, 288.0f, 0.0f);
	stickObj_.reset(DrawObjectForSprite2D::Create({ stickPos, {}, {1.0f,1.0f,1.0f} }, pStickSpr_));
	
	Vector3 buttonPos = (win / 2.0f) + Vector3(448.0f, 308.0f, 0.0f);
	buttonObj_.reset(DrawObjectForSprite2D::Create({ buttonPos, {}, {1.0f,1.0f,1.0f} }, pButtonSpr_));
	
	for (size_t i = 0; i < nums_.size(); i++)
	{
		nums_[i].Initialize();
		nums_[i].pos_ = win / 2.0f + Vector3(i * 160.0f, 0.0f, 0.0f);

		uiNumbers_[i].reset(UINumber::Create(static_cast<uint32_t>(i + 1), 10, 64.0f, false, &nums_[i].m_));
	}

	letterBox_.reset(new UILetterBox());

	letterBox_->Initialize(WinSize, 96.0f, 96.0f);

	stageIndex_ = StageManager::GetInstance()->CurrentStageIndex();

	transferVP_.Initialize();
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
	pLevel_->Update();
	
	logoObj_->Update();
	stickObj_->Update();
	buttonObj_->Update();

	letterBox_->Update();
	
	if (spKeys_->IsTrigger(DIK_LEFT) || spKeys_->IsTrigger(DIK_A))
	{
		stageIndex_--;
	}
	if (spKeys_->IsTrigger(DIK_RIGHT) || spKeys_->IsTrigger(DIK_D))
	{
		stageIndex_++;
	}

	if (stageIndex_ <= 0) { stageIndex_ = 0; }
	if (9 <= stageIndex_) { stageIndex_ = 9; }

	for (size_t i = 0; i < nums_.size(); i++)
	{
		Vector3 win = ConvertToVector3(WinSize);
		nums_[i].pos_ = win / 2.0f + Vector3(i * 160.0f - stageIndex_ * 160.0f, 0.0f, 0.0f);
	}

	for (size_t i = 0; i < nums_.size(); i++)
	{
		nums_[i].UpdateMatrix();
		uiNumbers_[i]->Update();
	}

	// ビュープロジェクション更新
	transferVP_.UpdateMatrix();


	// SPACE でゲーム開始
	if (spKeys_->IsTrigger(DIK_SPACE) || spPad_->IsTrigger(PadButton::XIP_A))
	{
		SceneExecutive::GetInstance()->Change("PLAY", "INFECTION", 2, 10);

		StageManager::GetInstance()->SetStageIndex(stageIndex_);
	}

	// ESC でタイトルに戻る
	if (spKeys_->IsTrigger(DIK_ESCAPE))
	{
		SceneExecutive::GetInstance()->Change("TITLE", "BLACKOUT", 20, 10);
	}
}
#pragma endregion


#pragma region 描画

void SelectScene::Draw()
{
	pLevel_->Draw();

	logoObj_->Draw("Sprite2DDefault", 1);
	buttonObj_->Draw("Sprite2DDefault", 1);
	stickObj_->Draw("Sprite2DDefault", 1);

	for (size_t i = 0; i < nums_.size(); i++)
	{
		uiNumbers_[i]->Draw("Sprite2DDefault", 1);
	}
	
	letterBox_->Draw("Sprite2DDefault", 2);
}
#pragma endregion