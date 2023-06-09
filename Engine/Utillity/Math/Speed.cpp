#include "Speed.h"
#include "MathUtil.h"

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
	
}