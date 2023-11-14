#include "PlaneCollider.h"
#include "PrimitiveCollisionDetection.h"

using YMath::PlaneCollider;
using YMath::Vector3;

PlaneCollider::PlaneCollider(
	Vector3* pFollowPoint, const
	Vector3& normal, const float distance, const Vector2& rectangle,
	const Vector3& offset, const bool isSlip) :
	BasePrimitiveCollider(pFollowPoint, offset, isSlip),
	normal_(normal.Normalized()), distance_(distance), rectangle_(rectangle)
{
}

PlaneCollider::PlaneCollider(
	Vector3* pFollowPoint, Vector3* pVelocity,
	const Vector3& normal, const float distance, const Vector2& rectangle,
	const Vector3& offset, const bool isPushBack, const bool isSlip) :
	BasePrimitiveCollider(pFollowPoint, pVelocity, offset, isPushBack, isSlip),
	normal_(normal.Normalized()), distance_(distance), rectangle_(rectangle)
{
}

void PlaneCollider::Initialize(
	Vector3* pFollowPoint,
	const Vector3& normal, const float distance, const Vector2& rectangle,
	const Vector3& offset, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, offset, isSlip);
	normal_ = normal;
	distance_ = distance;
	rectangle_ = rectangle;
}

void PlaneCollider::Initialize(
	Vector3* pFollowPoint, Vector3* pVelocity,
	const Vector3& normal, const float distance, const Vector2& rectangle,
	const Vector3& offset, const bool isPushBack, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, pVelocity, offset, isPushBack, isSlip);
	normal_ = normal;
	distance_ = distance;
	rectangle_ = rectangle;
}

bool PlaneCollider::CheckCollision(const BasePrimitiveCollider& other)
{
	if (isSlip_ || other.IsSlip()) { return false; }

	return other.CheckConcreteCollision(*this);
}

bool PlaneCollider::CheckConcreteCollision(const RayCollider& other) const
{
	return CollisionRayPlane(other, *this);
}
bool PlaneCollider::CheckConcreteCollision(const SphereCollider& other) const
{
	return CollisionPlaneSphere(*this, other);
}