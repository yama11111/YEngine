#include "Collider.h"

using YCollision::Collider;

void Collider::InitializeCollisionStatus(const InitStatus& state)
{
	radius_ = state.radius_;
	attribute_ = state.attribute_;
	mask_ = state.mask_;
	isSlip_ = state.isSlip_;
}