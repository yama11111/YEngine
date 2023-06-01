#include "MapChipCollider.h"
#include "mapchipCollider.h"
#include "mapchipCollider.h"

using YGame::MapChipCollider;

void MapChipCollider::Initialize(const InitStatus& state)
{
	scale_ = state.scale_;
	isLanding_ = false;
	isElderLanding_ = false;
}
