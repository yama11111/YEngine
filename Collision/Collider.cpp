#include "Collider.h"

using Collision::Collider;

void Collider::InitializeCollisionStatus(const CollisionStatus& state)
{
	radius_ = state.radius_;
	attribute_ = state.attribute_;
	mask_ = state.mask_;
	isSlip_ = state.isSlip_;
}