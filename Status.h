#pragma once
#include "Vec3.h"
class Status
{
public:
	int hp;
	bool isDeath;
	Vec3 direction;
	Vec3 speed;
	float power;
public:
	Status();
	void Initialize(const int hp, const float power);
	void CalcHp();
	void CalcSpeed();
};
