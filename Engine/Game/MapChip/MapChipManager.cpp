#include "MapChipManager.h"
#include <cassert>

using YGame::MapChipManager;

void MapChipManager::Load()
{
	if (mapDatas_.empty() == false)
	{
		for (size_t i = 0; i < mapDatas_.size(); i++)
		{
			mapDatas_[i].Clear();
		}
	}

	mapDatas_.resize(10);
	mapDatas_[0].Load("demo.csv");
}

void MapChipManager::Initialize(const InitStatus& status)
{
	currentIndex_ = status.mapIndex_;
	map_.Initialize(&mapDatas_[currentIndex_], status.leftTop_, status.chipSize_);
}

void MapChipManager::Reset()
{
	for (size_t i = 0; i < mapDatas_.size(); i++)
	{
		mapDatas_[i].CollReset();
	}

	map_.Reset();
}

void MapChipManager::Update()
{
	map_.Update();
}

void MapChipManager::Draw()
{
	map_.Draw();
}

void MapChipManager::Draw2D()
{
	mapDisp_.Draw();
}
