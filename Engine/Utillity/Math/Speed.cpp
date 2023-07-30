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

void Speed::Update(const Vector3& power)
{
	velocity_ += Vector3(
		acceleration_.x_ * power.x_,
		acceleration_.y_ * power.y_,
		acceleration_.z_ * power.z_);

	// Friction
	if (velocity_.x_ > 0) { velocity_.x_ -= 0.05f; }
	if (velocity_.x_ < 0) { velocity_.x_ += 0.05f; }
	
	if (isGravity_)
	{
		velocity_.y_ -= 0.1f;
	}

	velocity_ = YMath::Clamp(velocity_, -max_, max_);
}