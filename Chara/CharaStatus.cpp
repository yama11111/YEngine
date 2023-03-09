#include "CharaStatus.h"
#include <cassert>

void CharaStatus::Initialize(const InitStatus& state)
{
	assert(state.hp_ > 0);

	hp_ = state.hp_;
	isAlive_ = true;

	cheatTim_.Initialize(state.chaetTime_);
	isCheat_ = false;
}

void CharaStatus::Update()
{
	if (isAlive_ == false) { return; }

	cheatTim_.Update();
	if (cheatTim_.IsEnd())
	{
		isCheat_ = false;
		cheatTim_.Reset(false);
	}
}

void CharaStatus::Hit(const int damage)
{
	if (isAlive_ == false) { return; }
	if (isCheat_) { return; }

	hp_ -= damage;

	isCheat_ = true;
	cheatTim_.Reset(true);

	if (hp_ <= 0)
	{
		hp_ = 0;
		isAlive_ = false;
	}
}

void CharaStatus::SetHP(const int hp)
{
	hp_ = hp;

	if (hp_ <= 0)
	{
		hp_ = 0;
		isAlive_ = false;
	}
}
