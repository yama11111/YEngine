#include "Status.h"

Status::Status() :
	hp(0), isDeath(false), direction({0,0,0}), speed(), power(0.0f)
{
}

void Status::Initialize(const int hp, const float power)
{
	this->hp = hp;
	isDeath = false;
	direction = { 0,0,0 };
	this->power = power;
}

void Status::CalcHp()
{
	if (hp <= 0)
	{
		isDeath = true;
		hp = 0;
	}
}
void Status::CalcSpeed()
{
	speed = direction.Normalized();
	speed *= power;
}
