#include "MapChipCollider.h"

void MapChipCollider::InitializeMapCollisionStatus(const InitStatus& state)
{
	scale_ = state.scale_;
	isLanding_ = state.isLanding_;
}
