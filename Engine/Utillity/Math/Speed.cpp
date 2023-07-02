#include "Speed.h"
#include "MathUtil.h"
#include "Physics.h"

using YMath::Vector3;
using YMath::Speed;

void Speed::Initialize(const Vector3& acceleration, const Vector3& max, const bool isGravity)
{
	acceleration_ = acceleration;
	max_ = max;
	isGravity_ = isGravity;

	Reset();
}

void Speed::Reset()
{
	velocity_ = {};
}

void Speed::Update(const Vector3& direction)
{
	velocity_.x_ += acceleration_.x_ * direction.x_;
	velocity_.y_ += acceleration_.y_ * direction.y_;
	velocity_.z_ += acceleration_.z_ * direction.z_;

	// Friction
	
	if (isGravity_)
	{
		velocity_.y_ -= 0.1f;
	}

	velocity_ = YMath::Clamp(velocity_, -max_, max_);
}