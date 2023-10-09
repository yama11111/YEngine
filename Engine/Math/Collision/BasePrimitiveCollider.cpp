#include "BasePrimitiveCollider.h"

using YMath::BasePrimitiveCollider;
using YMath::Vector3;

void BasePrimitiveCollider::Initialize(Vector3* pFollowPoint, const Vector3& offset, const bool isSlip)
{
	pFollowPoint_ = pFollowPoint;
	offset_ = offset;
	isSlip_ = isSlip;
}

bool BasePrimitiveCollider::CheckConcreteCollision(const RayCollider& other) const
{
	other;
	return false;
}
bool BasePrimitiveCollider::CheckConcreteCollision(const PlaneCollider& other) const
{
	other;
	return false;
}
bool BasePrimitiveCollider::CheckConcreteCollision(const TriangleCollider& other) const
{
	other;
	return false;
}
bool BasePrimitiveCollider::CheckConcreteCollision(const SphereCollider& other) const
{
	other;
	return false;
}
bool BasePrimitiveCollider::CheckConcreteCollision(const Box2DCollider& other) const
{
	other;
	return false;
}

BasePrimitiveCollider::BasePrimitiveCollider(const bool isSlip) :
	pFollowPoint_(nullptr), offset_(Vector3()), isSlip_(isSlip)
{
}

BasePrimitiveCollider::BasePrimitiveCollider(Vector3* pFollowPoint, const Vector3& offset, const bool isSlip) :
	pFollowPoint_(pFollowPoint), offset_(offset), isSlip_(isSlip)
{
}
