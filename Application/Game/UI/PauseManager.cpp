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
	// �|�[�Y����
	isPause_ = false;

	// �|�[�Y����������
	isElderPause_ = false;

	// �I��
	current_ = PauseDrawer::Selection::Resume;
	
	pauseDra_.Reset();
	pauseDra_.SetSelection(current_);
}

void PauseManager::Update()
{
	// �|�[�Y�ۑ�
	isElderPause_ = isPause_;

	// TAB �� �|�[�Y�؂�ւ�
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

	// �|�[�Y��
	if (isPause_)
	{
		// �I��؂�ւ�
		ChangeSelect();

		// ���s (SPACE)
		if (Keys::GetInstance()->IsTrigger(DIK_SPACE) ||
			Pad::GetInstance()->IsTrigger(PadButton::XIP_A))
		{
			// Resume�Ȃ�
			if (current_ == PauseDrawer::Selection::Resume)
			{
				// ���Z�b�g
				ResumeReset();
			}
			else if (current_ == PauseDrawer::Selection::ReStart)
			{
				SceneManager::GetInstance()->Transition("PLAY", "WAVE");
			}
			// �J�ڂȂ�
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
	// �I��؂�ւ�
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
	// �|�[�Y����
	isPause_ = false;
	// �I��
	current_ = PauseDrawer::Selection::Resume;

	pauseDra_.ShutdownAnimation();
}
