#include "RayCollider.h"
#include "PrimitiveCollisionDetection.h"

using YMath::RayCollider;
using YMath::Vector3;

RayCollider::RayCollider(
	Vector3* pFollowPoint,
	const Vector3& direction,
	const Vector3& offset, const bool isSlip) :
	BasePrimitiveCollider(pFollowPoint, offset, isSlip),
	direction_(direction.Normalized())
{
}

RayCollider::RayCollider(
	Vector3* pFollowPoint, Vector3* pVelocity,
	const Vector3& direction,
	const Vector3& offset, const bool isPushBack, const bool isSlip) :
	BasePrimitiveCollider(pFollowPoint, pVelocity, offset, isPushBack, isSlip),
	direction_(direction.Normalized())
{
}

void RayCollider::Initialize(
	Vector3* pFollowPoint,
	const Vector3& direction,
	const Vector3& offset, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, offset, isSlip);
	direction_ = direction.Normalized();
}

void RayCollider::Initialize(
	Vector3* pFollowPoint, Vector3* pVelocity,
	const Vector3& direction,
	const Vector3& offset, const bool isPushBack, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, pVelocity, offset, isPushBack, isSlip);
	direction_ = direction.Normalized();
}

Vector3 RayCollider::Start() const
{
	return *pFollowPoint_ + offset_;
}

bool RayCollider::CheckCollision(const BasePrimitiveCollider& other)
{
	if (isSlip_ || other.IsSlip()) { return false; }

	return other.CheckConcreteCollision(*this);
}
bool RayCollider::CheckConcreteCollision(const PlaneCollider& other) const
{
	return CollisionRayPlane(*this, other);
}
bool RayCollider::CheckConcreteCollision(const TriangleCollider& other) const
{
	return CollisionRayTriangle(*this, other);
}
bool RayCollider::CheckConcreteCollision(const SphereCollider& other) const
{
	return CollisionRaySphere(*this, other);
}
