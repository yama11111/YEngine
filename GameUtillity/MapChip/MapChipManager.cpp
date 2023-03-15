#include "MapChipManager.h"
#include <cassert>

using YGame::MapChipManager;

void MapChipManager::Load(const LoadStatus& state)
{
	if (mapDatas_.empty() == false)
	{
		for (size_t i = 0; i < mapDatas_.size(); i++)
		{
			mapDatas_[i].Clear();
		}
	}

	mapDatas_.resize(1);
	mapDatas_[0].Load("demo.csv", state.pModels_, state.pSprites_);
}

void MapChipManager::Initialize(const InitStatus& state)
{
	currentIndex_ = state.mapIndex_;
	map_.Initialize(&mapDatas_[currentIndex_], state.leftTop_, state.chipSize_);
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

void MapChipManager::Draw(const YGame::ViewProjection& vp, YGame::LightGroup* pLightGroup, const UINT texIndex, YGame::Color* color)
{
	map_.Draw(vp, pLightGroup, texIndex, color);
}

void MapChipManager::Draw2D()
{
	mapDisp_.Draw();
}
