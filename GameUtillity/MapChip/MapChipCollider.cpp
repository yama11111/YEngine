#include "MapChipCollider.h"

using YGame::MapChipCollider;

void MapChipCollider::Initialize(const InitStatus& state)
{
	scale_ = state.scale_;
	isLanding_ = false;
	isElderLanding_ = false;
}
