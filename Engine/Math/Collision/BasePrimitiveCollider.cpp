#include "BasePrimitiveCollider.h"
#include <cassert>

using YMath::BasePrimitiveCollider;
using YMath::Vector3;

BasePrimitiveCollider::BasePrimitiveCollider(Vector3* pFollowPoint, const Vector3& offset, const bool isSlip) :
	pFollowPoint_(pFollowPoint), pVelocity_(nullptr), offset_(offset), isPushBack_(false), isSlip_(isSlip)
{
	assert(pFollowPoint);
}

BasePrimitiveCollider::BasePrimitiveCollider(
	Vector3* pFollowPoint, Vector3* pVelocity, const Vector3& offset, const bool isPushBack, const bool isSlip) :
	pFollowPoint_(pFollowPoint), pVelocity_(pVelocity), offset_(offset), isPushBack_(isPushBack), isSlip_(isSlip)
{
	assert(pFollowPoint);
	assert(pVelocity);
}

void BasePrimitiveCollider::Initialize(Vector3* pFollowPoint, const Vector3& offset, const bool isSlip)
{
	assert(pFollowPoint);

	pFollowPoint_ = pFollowPoint;
	pVelocity_ = nullptr;
	offset_ = offset;
	isPushBack_ = false;
	isSlip_ = isSlip;
}

void BasePrimitiveCollider::Initialize(
	Vector3* pFollowPoint, Vector3* pVelocity, const Vector3& offset, const bool isPushBack, const bool isSlip)
{
	assert(pFollowPoint);
	assert(pVelocity);

	pFollowPoint_ = pFollowPoint;
	pVelocity_ = pVelocity;
	offset_ = offset;
	isPushBack_ = isPushBack;
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