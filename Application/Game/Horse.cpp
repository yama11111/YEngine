#include "Horse.h"
#include "HorseDrawer.h"
#include "SphereCollider.h"

#include "CharacterConfig.h"

#include "CharacterManager.h"
#include "SnortAttack.h"

#include <cassert>

using YGame::Horse;
using YMath::Vector3;

void Horse::Initialize(const Transform::Status& status)
{
	ICharacter::Initialize(
		"Horse",
		status,
		PetConfig::kNormalAcceleration, PetConfig::kNormalMaxSpeed,
		PetConfig::kHP, PetConfig::kAttack, PetConfig::kInvincibleTime,
		new SphereCollider({}, AttributeType::ePet, AttributeType::eAll, PetConfig::kRadius),
		new HorseDrawer(DrawLocation::eCenter));

	isHit_ = false;

	jumpCounter_ = 0;

	maxJumpCount_ = PetConfig::kMaxJumpCount;
}

void Horse::Update()
{
	IPet::Update();
}

void Horse::Draw()
{
	ICharacter::Draw();
}

YGame::ICharacter::CollisionInfo Horse::GetCollisionInfo()
{
	CollisionInfo result;

	result.attribute_ = collider_->Attribute();
	result.pos_ = transform_->pos_;
	result.radius_ = PetConfig::kRadius;
	result.pStatus_ = &status_;
	result.pSelf_ = this;

	return result;
}

float Horse::RidingPosHeight()
{
	return PetConfig::kRiddenHeight;
}

void Horse::Attack()
{
	// UŒ‚V‹K¶¬
	SnortAttack* newAttack = new SnortAttack();

	newAttack->Initialize(
		{ transform_->pos_, {}, {1.0f,1.0f,1.0f} },
		SnortAttackConfig::kAliveTime,
		SnortAttackConfig::kPower
	);

	CharacterManager::GetInstance()->PushBack(newAttack);
}
