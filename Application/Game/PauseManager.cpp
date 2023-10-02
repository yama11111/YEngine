#include "PauseManager.h"

#include "SceneManager.h"

#include "Keys.h"
#include "Pad.h"

#include "Def.h"

using YGame::PauseManager;

using YMath::Vector3;

using YInput::Keys;
using YInput::Pad;
using YInput::PadButton;

namespace 
{
	const YMath::Vector4 kOnColor = { 1.0f,1.0f,1.0f,1.0f };

	const YMath::Vector4 kOffColor = { 0.3f,0.3f,0.3f,1.0f };


	YGame::Sprite2D* pPause = nullptr;
	
	YGame::Sprite2D* pCurten = nullptr;
	
	YGame::Sprite2D* pRestart = nullptr;
	
	YGame::Sprite2D* pReset = nullptr;
	
	YGame::Sprite2D* pSelect = nullptr;
}

void PauseManager::StaticInitialize()
{
	pPause = Sprite2D::Create({ {"Texture0", Texture::Load("pause/pause.png")} });
	
	pCurten = Sprite2D::Create({ {"Texture0", Texture::Load("white1x1.png")} });
	
	pRestart = Sprite2D::Create({ {"Texture0", Texture::Load("pause/restart.png")} });
	
	pReset = Sprite2D::Create({ {"Texture0", Texture::Load("pause/reset.png")} });
	
	pSelect = Sprite2D::Create({ {"Texture0", Texture::Load("pause/select.png")} });
}

void PauseManager::Initialize()
{
	pause_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pPause));

	curten_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pCurten));
	curtenColor_.reset(ConstBufferObject<CBColor>::Create());
	curten_->InsertConstBuffer(curtenColor_.get());

	restart_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pRestart));
	restartColor_.reset(ConstBufferObject<CBColor>::Create());
	restart_->InsertConstBuffer(restartColor_.get());

	reset_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pReset));
	resetColor_.reset(ConstBufferObject<CBColor>::Create());
	reset_->InsertConstBuffer(resetColor_.get());

	select_.reset(DrawObjectForSprite2D::Create(Transform::Status::Default(), pSelect));
	selectColor_.reset(ConstBufferObject<CBColor>::Create());
	select_->InsertConstBuffer(selectColor_.get());


	// 選択スケールイージング
	selectScaleEas_.Initialize({ -0.25f,-0.25f,0.0f }, {}, 3.0f);

	Reset();
}

void PauseManager::Reset()
{
	pause_->transform_.Initialize({ { WinSize.x_ / 2.0f, 160.0f, 0.0f },{},{1.0f,1.0f,1.0f} });
	curten_->transform_.Initialize({ Vector3(WinSize.x_, WinSize.y_, 0.0f) / 2.0f, {}, { WinSize.x_, WinSize.y_, 0.0f } });
	restart_->transform_.Initialize({ { WinSize.x_ / 2.0f, 320.0f, 0.0f },{},{1.0f,1.0f,1.0f} });
	reset_->transform_.Initialize({ { WinSize.x_ / 2.0f, 480.0f, 0.0f },{},{1.0f,1.0f,1.0f} });
	select_->transform_.Initialize({ { WinSize.x_ / 2.0f, 640.0f, 0.0f },{},{1.0f,1.0f,1.0f} });

	// ポーズ中か
	isPause_ = false;

	// ポーズ中だったか
	isElderPause_ = false;

	// 選択
	current_ = Selection::Resume;

	restartPow_.Initialize(20);
	resetPow_.Initialize(20);
	selectPow_.Initialize(20);

	// curtenColor
	curtenColor_->data_.baseColor = { 0.0f,0.0f,0.0f,0.75f };
}

void PauseManager::Update()
{
	// ポーズ保存
	isElderPause_ = isPause_;

	// TAB → ポーズ切り替え
	if (Keys::GetInstance()->IsTrigger(DIK_ESCAPE) ||
		Pad::GetInstance()->IsTrigger(PadButton::XIP_MENU))
	{
		// ポーズ中じゃないなら
		if (isPause_ == false)
		{
			// ポーズに
			isPause_ = true;
		}
		// 違うなら
		else
		{
			// リセット
			ResumeReset();
		}
	}

	// ポーズ中じゃないなら弾く
	if (isPause_ == false) { return; }

	// 選択切り替え
	if (Keys::GetInstance()->IsTrigger(DIK_W) || Keys::GetInstance()->IsTrigger(DIK_UP) ||
		Pad::GetInstance()->IsTrigger(PadButton::XIP_UP))
	{
		if (current_ == Selection::Resume)
		{
			current_ = Selection::Change;
		}
		else if (current_ == Selection::ReStart)
		{
			current_ = Selection::Resume;
		}
		else if (current_ == Selection::Change)
		{
			current_ = Selection::ReStart;
		}
	}

	if (Keys::GetInstance()->IsTrigger(DIK_S) || Keys::GetInstance()->IsTrigger(DIK_DOWN) ||
		Pad::GetInstance()->IsTrigger(PadButton::XIP_DOWN))
	{
		if (current_ == Selection::Resume)
		{
			current_ = Selection::ReStart;
		}
		else if (current_ == Selection::ReStart)
		{
			current_ = Selection::Change;
		}
		else if (current_ == Selection::Change)
		{
			current_ = Selection::Resume;
		}
	}

	// 選択しているか分かるように
	if (current_ == Selection::Resume)
	{
		restartColor_->data_.baseColor = kOnColor;
		resetColor_->data_.baseColor = kOffColor;
		selectColor_->data_.baseColor = kOffColor;
	}
	else if (current_ == Selection::ReStart)
	{
		restartColor_->data_.baseColor = kOffColor;
		resetColor_->data_.baseColor = kOnColor;
		selectColor_->data_.baseColor = kOffColor;
	}
	else if (current_ == Selection::Change)
	{
		restartColor_->data_.baseColor = kOffColor;
		resetColor_->data_.baseColor = kOffColor;
		selectColor_->data_.baseColor = kOnColor;
	}

	restartPow_.Update((current_ == Selection::Resume));
	resetPow_.Update((current_ == Selection::ReStart));
	selectPow_.Update((current_ == Selection::Change));

	pause_->Update();
	curten_->Update();
	restart_->Update({ {},{},{selectScaleEas_.InOut(restartPow_.Ratio())} });
	reset_->Update({ {},{},{selectScaleEas_.InOut(resetPow_.Ratio())} });
	select_->Update({ {},{},{selectScaleEas_.InOut(selectPow_.Ratio())} });

	// 実行 (SPACE)
	if (Keys::GetInstance()->IsTrigger(DIK_SPACE) || 
		Pad::GetInstance()->IsTrigger(PadButton::XIP_A))
	{
		// Resumeなら
		if (current_ == Selection::Resume)
		{
			// リセット
			ResumeReset();
		}
		else if (current_ == Selection::ReStart)
		{
			SceneManager::GetInstance()->Transition("PLAY", "WIND");
		}
		// 遷移なら
		else if (current_ == Selection::Change)
		{
			SceneManager::GetInstance()->Transition("SELECT", "BLACKOUT");
		}
	}
}

void PauseManager::Draw()
{
	if (isPause_ == false) { return; }

	curten_->Draw("Sprite2DDefault", 2);
	
	pause_->Draw("Sprite2DDefault", 1);
	restart_->Draw("Sprite2DDefault", 1);
	reset_->Draw("Sprite2DDefault", 1);
	select_->Draw("Sprite2DDefault", 1);
}

void PauseManager::ResumeReset()
{	
	// ポーズ中か
	isPause_ = false;
	// 選択
	current_ = Selection::Resume;

	// パワーリセット
	restartPow_.Reset();
	resetPow_.Reset();
	selectPow_.Reset();
}
