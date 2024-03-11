#include "StageStatusManager.h"
#include "MathUtil.h"
#include <cassert>
#include <string>
#include <cstdio>
#include <cstring>

using YGame::StageStatusManager;

namespace 
{
	const std::string kFileName = "Resources/StageData/stage_statuses.txt";
}

void StageStatusManager::Load()
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
		std::array<int, 3> mission = {};
		std::array<int, 3> isClear = {};
		end = fscanf_s(fp, "%d %d %d %d %d %d", 
			&mission[0], &isClear[0], 
			&mission[1], &isClear[1], 
			&mission[2], &isClear[2]);
		
		assert(end != EOF);
		
		statuses_.emplace_back();
		
		statuses_[index].isTutorial = static_cast<bool>(isTutorial);
		for (size_t i = 0; i < 3; i++)
		{
			statuses_[index].mission[i] = static_cast<uint32_t>(mission[i]);
			statuses_[index].isMissionClear[i] = static_cast<bool>(isClear[i]);
		}

		index++;
	}

	fclose(fp);
}

void StageStatusManager::Save()
{
	FILE* fp = NULL;
	errno_t err;

	// 書き込み用ファイル を開く
	err = fopen_s(&fp, kFileName.c_str(), "w");
	assert(err == 0);

	// ファイルに書き込み (1行 : 1データ)
	for (size_t i = 0; i < statuses_.size(); i++)
	{
		fprintf(fp, "%d %d %d %d %d %d %d", 
			static_cast<int>(statuses_[i].isTutorial),
			static_cast<int>(statuses_[i].mission[0]),
			static_cast<int>(statuses_[i].isMissionClear[0]),
			static_cast<int>(statuses_[i].mission[1]),
			static_cast<int>(statuses_[i].isMissionClear[1]),
			static_cast<int>(statuses_[i].mission[2]), 
			static_cast<int>(statuses_[i].isMissionClear[2])); 
		fputc('\n', fp);
	}

	fclose(fp);
}

void StageStatusManager::Clear()
{
	statuses_.clear();
}

uint32_t StageStatusManager::CurrentStageIndex() const
{
	return stageIndex;
}

uint32_t StageStatusManager::MaxStageNum() const
{
	return static_cast<uint32_t>(statuses_.size());
}

StageStatusManager::StageStatus StageStatusManager::Status(const size_t index) const
{
	assert(0 <= index && index < statuses_.size());

	return statuses_[index];
}

void StageStatusManager::SetCurrentStageStatus(const uint32_t score)
{
	StageStatus& status = statuses_[static_cast<size_t>(stageIndex)];
	for (size_t i = 0; i < status.isMissionClear.size(); i++)
	{
		if (status.isMissionClear[i]) { continue; }
		if (status.mission[i] <= score)
		{
			status.isMissionClear[i] = true;
		}
	}
}

void StageStatusManager::SetStageIndex(const uint32_t index)
{
	stageIndex = YMath::Clamp<uint32_t>(index, 0, MaxStageNum());
}

StageStatusManager* StageStatusManager::GetInstance()
{
	static StageStatusManager instance;
	return &instance;
}
