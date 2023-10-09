#include "StageManager.h"
#include "ScoreManager.h"
#include "SceneManager.h"
#include "MathUtil.h"
#include <cassert>
#include <cstdio>
#include <cstring>

using YGame::StageManager;

namespace 
{
	const std::string kFileName = "Resources/StageData/stage_statuses.txt";
}

void StageManager::Load()
{
	statuses_.clear();

	FILE* fp = NULL;
	errno_t err;

	// 読み込み用ファイル を開く
	err = fopen_s(&fp, kFileName.c_str(), "r");
	assert(err == 0);

	// ファイル終端まで読み込み
	size_t index = 0;
	while (true)
	{
		int end = 0;
		
		// チュートリアルフラグ
		int isTutorial = 0;
		end = fscanf_s(fp, "%d", &isTutorial);
		
		if (end == EOF) { break; }
		
		// ミッション
		std::array<int, 3> isClear = {};
		end = fscanf_s(fp, "%d %d %d", &isClear[0], &isClear[1], &isClear[2]);
		
		assert(end != EOF);
		
		statuses_.emplace_back();
		
		statuses_[index].isTutorial = static_cast<bool>(isTutorial);
		for (size_t i = 0; i < isClear.size(); i++)
		{
			statuses_[index].isMissionClear[i] = static_cast<bool>(isClear[i]);
		}

		index++;
	}

	fclose(fp);
}

void StageManager::Save()
{
	FILE* fp = NULL;
	errno_t err;

	// 書き込み用ファイル を開く
	err = fopen_s(&fp, kFileName.c_str(), "w");
	assert(err == 0);

	// ファイルに書き込み (1行 : 1データ)
	for (size_t i = 0; i < statuses_.size(); i++)
	{
		fprintf(fp, "%d %d %d %d", 
			static_cast<int>(statuses_[i].isTutorial),
			static_cast<int>(statuses_[i].isMissionClear[0]),
			static_cast<int>(statuses_[i].isMissionClear[1]),
			static_cast<int>(statuses_[i].isMissionClear[2])); 
		fputc('\n', fp);
	}

	fclose(fp);
}

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
	stageIndex = YMath::Clamp<uint32_t>(stageIndex, 0, MaxStageNum());

	if (SceneManager::GetInstance()->IsTransition() == false)
	{
		if (isGameOver_)
		{
			SceneManager::GetInstance()->Transition("PLAY", "BLACKOUT");
		}

		if (isStageClear_)
		{
			statuses_[static_cast<size_t>(stageIndex)].isMissionClear[0] = true;
			statuses_[static_cast<size_t>(stageIndex)].isMissionClear[1] = true;
			statuses_[static_cast<size_t>(stageIndex)].isMissionClear[2] = true;

			Save();

			SceneManager::GetInstance()->Transition("SELECT", "WAVE");
		}
	}
}

uint32_t StageManager::CurrentStageIndex() const
{
	return stageIndex;
}

uint32_t StageManager::MaxStageNum() const
{
	return static_cast<uint32_t>(statuses_.size());
}

StageManager::StageStatus StageManager::Status(const size_t index) const
{
	assert(0 <= index && index < statuses_.size());

	return statuses_[index];
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
