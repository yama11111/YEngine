#include "CharaStatus.h"
#include <cassert>

void CharaStatus::InitializeCharaStatus(const InitStatus& state)
{
	assert(state.hp_ > 0);

	hp_ = state.hp_;
	isAlive_ = true;

	cheatT_.Initialize(state.chaetTime_);
	isCheat_ = false;
}

void CharaStatus::UpdateCharaStatus()
{
	if (isAlive_ == false) { return; }
	if (isCheat_) { return; }

	cheatT_.Update();
	if (cheatT_.IsEnd())
	{
		isCheat_ = false;
		cheatT_.Reset(false);
	}
}

void CharaStatus::Hit(const int damage)
{
	if (isAlive_ == false) { return; }
	if (isCheat_) { return; }

	hp_ -= damage;

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
