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

void PauseManager::Initialize()
{
	pauseDra_.Initialize();
	
	Reset();
}

void PauseManager::Reset()
{
	// ポーズ中か
	isPause_ = false;

	// ポーズ中だったか
	isElderPause_ = false;

	// 選択
	current_ = PauseDrawer::Selection::Resume;
	
	pauseDra_.Reset();
	pauseDra_.SetSelection(current_);
}

void PauseManager::Update()
{
	// ポーズ保存
	isElderPause_ = isPause_;

	// TAB → ポーズ切り替え
	if (Keys::GetInstance()->IsTrigger(DIK_ESCAPE) ||
		Pad::GetInstance()->IsTrigger(PadButton::XIP_MENU))
	{
		if (isPause_ == false)
		{
			isPause_ = true;
			pauseDra_.BootAnimation();
		}
		else
		{
			ResumeReset();
		}
	}

	// ポーズ中
	if (isPause_)
	{
		// 選択切り替え
		ChangeSelect();

		// 実行 (SPACE)
		if (Keys::GetInstance()->IsTrigger(DIK_SPACE) ||
			Pad::GetInstance()->IsTrigger(PadButton::XIP_A))
		{
			// Resumeなら
			if (current_ == PauseDrawer::Selection::Resume)
			{
				// リセット
				ResumeReset();
			}
			else if (current_ == PauseDrawer::Selection::ReStart)
			{
				SceneManager::GetInstance()->Transition("PLAY", "WAVE");
			}
			// 遷移なら
			else if (current_ == PauseDrawer::Selection::Change)
			{
				SceneManager::GetInstance()->Transition("SELECT", "WAVE_REV");
			}
		}
	}

	pauseDra_.Update();
}

void PauseManager::Draw()
{
	pauseDra_.Draw();
}

void PauseManager::ChangeSelect()
{
	// 選択切り替え
	if (Keys::GetInstance()->IsTrigger(DIK_W) || Keys::GetInstance()->IsTrigger(DIK_UP) ||
		Pad::GetInstance()->IsTrigger(PadButton::XIP_UP))
	{
		if (current_ == PauseDrawer::Selection::Resume)
		{
			current_ = PauseDrawer::Selection::Change;
		}
		else if (current_ == PauseDrawer::Selection::ReStart)
		{
			current_ = PauseDrawer::Selection::Resume;
		}
		else if (current_ == PauseDrawer::Selection::Change)
		{
			current_ = PauseDrawer::Selection::ReStart;
		}
	}

	if (Keys::GetInstance()->IsTrigger(DIK_S) || Keys::GetInstance()->IsTrigger(DIK_DOWN) ||
		Pad::GetInstance()->IsTrigger(PadButton::XIP_DOWN))
	{
		if (current_ == PauseDrawer::Selection::Resume)
		{
			current_ = PauseDrawer::Selection::ReStart;
		}
		else if (current_ == PauseDrawer::Selection::ReStart)
		{
			current_ = PauseDrawer::Selection::Change;
		}
		else if (current_ == PauseDrawer::Selection::Change)
		{
			current_ = PauseDrawer::Selection::Resume;
		}
	}

	pauseDra_.SetSelection(current_);
}

void PauseManager::ResumeReset()
{	
	// ポーズ中か
	isPause_ = false;
	// 選択
	current_ = PauseDrawer::Selection::Resume;

	pauseDra_.ShutdownAnimation();
}
