#pragma once

class Status
{
public:
	int hp = 0;
	bool isDeath = false;
	bool isHit = false;
	int limit = 0;
	int invT = 0;
	bool isInvisible = false;
public:
	Status();
	void Initialize(const int hp, const int limit);
	void Update();
	void Damage(const int damage);
};
