#include "Speed.h"
#include "MathUtillity.h"

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
	value_ = {};
}

void Speed::Update(const Vector3& power)
{
	Calculate(value_.x_, power.x_, acceleration_.x_, max_.x_, spWorldRuler_->GetFriction());
	if (isGravity_)
	{
		Gravity(value_.y_, power.y_, acceleration_.y_, max_.y_, spWorldRuler_->GetGravity());
	}
	else
	{
		Calculate(value_.y_, power.y_, acceleration_.y_, max_.y_, spWorldRuler_->GetFriction());
	}
	Calculate(value_.z_, power.z_, acceleration_.z_, max_.z_, spWorldRuler_->GetFriction());

	value_*= spWorldRuler_->GetTimeSpeed();
}

void Speed::Calculate(float& value, const float power, const float acceleration, const float max, const float dekey)
{
	value += power * acceleration;
	if (power == 0.0f)
	{
		if (value > 0.0f)
		{
			value -= dekey;
			if (value <= 0.0f) { value = 0.0f; }
		}
		if (value < 0.0f)
		{
			value += dekey;
			if (value >= 0.0f) { value = 0.0f; }
		}
	}
	value = Clamp(value, -max, +max);
}

void Speed::Gravity(float& value, const float power, const float acceleration, const float max, const float dekey)
{
	value += power * acceleration;
	if (power == 0.0f)
	{
		value -= dekey;
	}
	value = Clamp(value, -max * 2.0f, +max);
}
