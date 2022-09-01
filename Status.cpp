#include "Status.h"

Status::Status() :
	hp(0), isDeath(false)
{
}

void Status::Initialize(const int hp, const int limit)
{
	this->hp = hp;
	this->limit = limit;
	invT = limit;
	isDeath = false;
	isHit = false;
	isInvisible = false;
}

void Status::Update()
{
	if (isInvisible)
	{
		invT--;
		if (invT <= 0) 
		{
			invT = limit;
			isInvisible = false;
		}
	}
}

void Status::Damage(const int damage)
{
	if (!isInvisible)
	{
		if (limit != 0) isInvisible = true;
		hp -= damage;
		if (hp <= 0)
		{
			isDeath = true;
			hp = 0;
		}
		else isDeath = false;
	}
}