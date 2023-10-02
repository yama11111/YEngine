#include "StageManager.h"
#include "SceneManager.h"

using YGame::StageManager;

void StageManager::Initialize()
{
	stageIndex = 0;

	Reset();
}

void StageManager::Reset()
{
	isGameOver_ = false;

	isStageClear_ = false;
}

void StageManager::Update()
{
	if (SceneManager::GetInstance()->IsTransition() == false)
	{
		if (isGameOver_)
		{
			SceneManager::GetInstance()->Transition("PLAY", "BLACKOUT");
		}

		if (isStageClear_)
		{
			SceneManager::GetInstance()->Transition("SELECT", "WIND");
		}
	}
}

uint32_t StageManager::CurrentStageIndex() const
{
	return stageIndex;
}

void StageManager::SetStageIndex(const uint32_t index)
{
	stageIndex = index;
}

void StageManager::GameOver()
{
	isGameOver_ = true;
}

void StageManager::ClearStage()
{
	isStageClear_ = true;
}

StageManager* StageManager::GetInstance()
{
	static StageManager instance;
	return &instance;
}
