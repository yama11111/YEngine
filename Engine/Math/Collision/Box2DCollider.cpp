#include "Box2DCollider.h"
#include "PrimitiveCollisionDetection.h"

using YMath::Vector2;
using YMath::Vector3;
using YMath::Box2DCollider;

Box2DCollider::Box2DCollider(
	Vector3* pFollowPoint,
	const Vector2& rectSize,
	const Vector3& offset, const bool isSlip) :
	BasePrimitiveCollider(pFollowPoint, offset, isSlip),
	rectSize_(Vector2(fabsf(rectSize.x_), fabsf(rectSize.y_)))
{
}

Box2DCollider::Box2DCollider(
	Vector3* pFollowPoint, Vector3* pVelocity,
	const Vector2& rectSize,
	const Vector3& offset, const bool isPushBack, const bool isSlip) :
	BasePrimitiveCollider(pFollowPoint, pVelocity, offset, isPushBack, isSlip),
	rectSize_(Vector2(fabsf(rectSize.x_), fabsf(rectSize.y_)))
{
}

void Box2DCollider::Initialize(
	Vector3* pFollowPoint,
	const Vector2& rectSize,
	const Vector3& offset, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, offset, isSlip);
	rectSize_ = Vector2(fabsf(rectSize.x_), fabsf(rectSize.y_));
}

void Box2DCollider::Initialize(
	Vector3* pFollowPoint, Vector3* pVelocity,
	const Vector2& rectSize,
	const Vector3& offset, const bool isPushBack, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, pVelocity, offset, isPushBack, isSlip);
	rectSize_ = Vector2(fabsf(rectSize.x_), fabsf(rectSize.y_));
}

Vector2 Box2DCollider::Center() const
{
	Vector2 result = Vector2(pFollowPoint_->x_, pFollowPoint_->y_) + Vector2(offset_.x_, offset_.y_);

	if (pVelocity_)
	{
		result += Vector2(pVelocity_->x_, pVelocity_->y_);
	}

	return result;
}

bool Box2DCollider::CheckCollision(const BasePrimitiveCollider& other)
{
	if (isSlip_ || other.IsSlip()) { return false; }

	if (isPushBack_)
	{
		return other.CheckConcreteCollisionAndPushBack(*this);
	}
	else
	{
		return other.CheckConcreteCollision(*this);
	}
}
bool Box2DCollider::CheckConcreteCollision(const Box2DCollider& other) const
{
	return CollisionBoxBox2D(*this, other);
}

bool Box2DCollider::CheckConcreteCollisionAndPushBack(Box2DCollider& other) const
{
	return CollisionAndPushBackBoxBox2D(*this, other);
}
