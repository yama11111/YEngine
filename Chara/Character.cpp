#include "Character.h"
#include "CharaConfig.h"
#include "MapChipManager.h"
#include <cassert>

using YMath::Vec3;
using CharaConfig::GravityPower;

MapChipPointer* Character::pMapChip_ = nullptr;
YParticle::ParticleManager* Character::pParticleMan_ = nullptr;

void Character::InitializeCharacter(YGame::ObjectModel::Status state)
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

	//obj_.color_ = color;

	if (obj_.pos_.y_ <= -200.0f)
	{
		Hit(1000);
	}

	if (isAlive()) 
	{
		pParticleMan_->EmitExprosion(obj_.pos_, 25.0f, { 0.25f, 0.75f, 0.75f, 1.0f }, 40, 25);
	}
}

void Character::SetMapChipPointer(const StaticInitStatus& state)
{
	assert(state.pMapChip_);
	assert(state.pParticleMan_);

	pMapChip_ = state.pMapChip_;
	pParticleMan_ = state.pParticleMan_;
}
