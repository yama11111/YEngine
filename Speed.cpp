#include "Speed.h"

Speed::Speed() :
	value(), direction(),
	power(0.0f) 
{
}

void Speed::Initialize(const Vec3& direction, const float power)
{
	this->value = { 0,0,0 };
	this->direction = direction;
	this->power = power;
}

void Speed::Update(const bool advance)
{
	if (advance)
	{
		value = direction.Normalized();
		value *= power;
	}
	else value = {};
}