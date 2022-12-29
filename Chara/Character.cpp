#include "Character.h"
#include "CharaConfig.h"
#include "MapChipManager.h"
#include <cassert>

using YMath::Vec3;
using CharaConfig::GravityPower;

MapChipPointer* Character::pMapChip_ = nullptr;

void Character::InitializeCharacter(YGame::Object::Status state)
{
	obj_.Initialize(state);
	speed_ = {};
}

void Character::UpdateGravity()
{
	speed_.y_ -= GravityPower;

	pMapChip_->Collision(*this);

	if (IsElderLanding() == false && 
		IsLanding())
	{
		Vec3 squash = obj_.scale_ * CharaConfig::SlimeAct::SquashValue;
		squash.y_ *= -1.0f;

		ActivateSlimeAct({ squash }, CharaConfig::SlimeAct::Frame);
	}
}

void Character::SetMapChipPointer(MapChipPointer* pMapChip)
{
	assert(pMapChip);
	pMapChip_ = pMapChip;
}
