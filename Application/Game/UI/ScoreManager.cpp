#include "ScoreManager.h"
#include "StageStatusManager.h"
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
	coinCounter_ = 0;
	speedLevel_ = 1;
}

void ScoreManager::StartScoreMeasurement()
{
	currentScore_ = 0;
	coinCounter_ = 0;
	speedLevel_ = 1;
}

void ScoreManager::EndScoreMeasurement()
{
	size_t index = static_cast<size_t>(StageStatusManager::GetInstance()->CurrentStageIndex());

	scores_[index] = currentScore_;
}

void ScoreManager::AddScore(const uint32_t scoreVal)
{
	currentScore_ += scoreVal;
}

const uint32_t ScoreManager::Score(const size_t index) const
{
	assert(0 <= index || index < scores_.size());

	return scores_[index];
}

const uint32_t ScoreManager::ScoreInCurrentStage() const
{
	return currentScore_;
}

void ScoreManager::AddCoin(const uint32_t coinVal)
{
	coinCounter_ += coinVal;
}

const uint32_t ScoreManager::Coin() const
{
	return coinCounter_;
}

void ScoreManager::SetHP(const uint32_t hp)
{
	hp_ = hp;
}

void ScoreManager::SetMaxHP(const uint32_t maxHP)
{
	maxHP_ = maxHP;
}

const uint32_t ScoreManager::HP() const
{
	return hp_;
}

const uint32_t ScoreManager::MaxHP() const
{
	return maxHP_;
}

void ScoreManager::AddSpeedLevel()
{
	speedLevel_++;
}

const uint32_t ScoreManager::SpeedLevel() const
{
	return speedLevel_;
}

ScoreManager* ScoreManager::GetInstance()
{
	static ScoreManager instance;
	return &instance;
}
