#include "SphereCollider.h"
#include "PrimitiveCollisionDetection.h"

using YMath::Vector3;
using YMath::SphereCollider;

SphereCollider::SphereCollider(
	Vector3* pFollowPoint,
	const float radius,
	const Vector3& offset, const bool isSlip) :
	BasePrimitiveCollider(pFollowPoint, offset, isSlip),
	radius_(fabsf(radius))
{
}

SphereCollider::SphereCollider(
	Vector3* pFollowPoint, Vector3* pVelocity,
	const float radius,
	const Vector3& offset, const bool isPushBack, const bool isSlip) :
	BasePrimitiveCollider(pFollowPoint, pVelocity, offset, isPushBack, isSlip),
	radius_(fabsf(radius))
{
}

void SphereCollider::Initialize(
	Vector3* pFollowPoint,
	const float radius,
	const Vector3& offset, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, offset, isSlip);
	radius_ = fabsf(radius);
}

void SphereCollider::Initialize(
	Vector3* pFollowPoint, Vector3* pVelocity,
	const float radius,
	const Vector3& offset, const bool isPushBack, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, pVelocity, offset, isPushBack, isSlip);
	radius_ = fabsf(radius);
}

Vector3 SphereCollider::Center() const
{
	Vector3 result = *pFollowPoint_ + offset_;
	
	if (pVelocity_) 
	{
		result += *pVelocity_; 
	}
	
	return result;
}

bool SphereCollider::CheckCollision(const BasePrimitiveCollider& other)
{
	if (isSlip_ || other.IsSlip()) { return false; }

	return other.CheckConcreteCollision(*this);
}

bool SphereCollider::CheckConcreteCollision(const RayCollider& other) const
{
	return CollisionRaySphere(other, *this);
}
bool SphereCollider::CheckConcreteCollision(const PlaneCollider& other) const
{
	return CollisionPlaneSphere(other, *this);
}
bool SphereCollider::CheckConcreteCollision(const TriangleCollider& other) const
{
	return CollisionTriangleSphere(other, *this);
}
bool SphereCollider::CheckConcreteCollision(const SphereCollider& other) const
{
	return CollisionSphereSphere(*this, other);
}