#pragma once
#include "Vec3.h"

class Speed 
{
public:
	Vec3 value;
	Vec3 direction;
	float power;
public:
	Speed();
	void Initialize(const Vec3& direction, const float power);
	void Update(const bool advance);
};