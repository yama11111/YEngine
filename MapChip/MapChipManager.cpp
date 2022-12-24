#include "MapChipManager.h"
#include <cassert>

void MapChipPointer::Collision(MapChipCollider& collider)
{
	assert(pMapChip_);
	pMapChip_->PerfectPixelCollision(collider);
}

void MapChipManager::Load(const LoadStatus& state)
{
	maps_.resize(1);
	maps_[0].Load({ "stage1.csv", state.pModel_, state.tex_, state.pSprite_ });

}

void MapChipManager::Initialize(const InitStatus& state)
{
	for (size_t i = 0; i < maps_.size(); i++)
	{
		maps_[i].Initialize({state.leftTop_, state.chipSize_});
	}

	currentIndex_ = state.mapIndex_;
	current_.SetMapChip(&maps_[state.mapIndex_]);
}

void MapChipManager::Reset()
{
	for (size_t i = 0; i < maps_.size(); i++)
	{
		maps_[i].Reset();
	}
}

void MapChipManager::Update()
{
	maps_[currentIndex_].Update();
}

void MapChipManager::Draw(const YGame::ViewProjection& vp)
{
	maps_[currentIndex_].Draw(vp);
}

void MapChipManager::Draw2D()
{
	maps_[currentIndex_].Draw2D();
}
