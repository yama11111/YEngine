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

	InitializeSlimeAction();
	InitializeHitAction();
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

		ActivateSlimeAction({ {}, squash }, CharaConfig::SlimeAct::Frame);
	}
}

void Character::UpdateCharacter()
{
	UpdateCharaStatus();
	UpdateSlimeAction();
	UpdateHitAction();

	YMath::Vec4 color = YMath::Vec4(1.0f, 1.0f, 1.0f, 1.0f);
	if (IsActHitAction()) { color = HitActionColor(); }

	obj_.color_ = color;
}

void Character::SetMapChipPointer(MapChipPointer* pMapChip)
{
	assert(pMapChip);
	pMapChip_ = pMapChip;
}
