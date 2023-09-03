#include "StageManager.h"
#include "SceneExecutive.h"

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
	if (TransitionManager::GetInstance()->IsAct() == false)
	{
		if (isGameOver_)
		{
			SceneExecutive::GetInstance()->Change("PLAY", "BLACKOUT", 10, 5);
		}

		if (isStageClear_)
		{
			SceneExecutive::GetInstance()->Change("PLAY", "INFECTION", 2, 5);
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
