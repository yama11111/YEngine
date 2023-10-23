#include "ScoreManager.h"
#include "StageManager.h"
#include <cassert>

using YGame::ScoreManager;

void ScoreManager::Load()
{

}

void ScoreManager::Save()
{

}

void ScoreManager::Initialize()
{
	scores_.clear();
	scores_.resize(3);

	currentScore_ = 0;
}

void ScoreManager::StartScoreMeasurement()
{
	currentScore_ = 0;
}

void ScoreManager::EndScoreMeasurement()
{
	size_t index = static_cast<size_t>(StageManager::GetInstance()->CurrentStageIndex());

	scores_[index] = currentScore_;
}

void ScoreManager::AddScore(const uint32_t scoreVal)
{
	currentScore_ += scoreVal;
}

uint32_t ScoreManager::Score(const size_t index)
{
	assert(0 <= index || index < scores_.size());

	return scores_[index];
}

uint32_t ScoreManager::ScoreInCurrentStage()
{
	return currentScore_;
}

ScoreManager* ScoreManager::GetInstance()
{
	static ScoreManager instance;
	return &instance;
}
