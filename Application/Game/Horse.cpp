#include "Horse.h"
#include "HorseDrawer.h"
#include "PrimitiveCollider.h"
#include "MapChipCollisionBitConfig.h"

#include "CharacterConfig.h"
#include "AnimationConfig.h"

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
		new GameCollider(transform_.get(), AttributeType::ePet, AttributeType::eAll),
		new HorseDrawer(1));

	collider_->PushBack(new YMath::SphereCollider(Vector3(), PetConfig::kRadius));

	isHit_ = false;

	jumpCounter_ = 0;

	maxJumpCount_ = PetConfig::kMaxJumpCount;

	// �����A�j���[�V����
	drawer_->PlayAnimation(
		static_cast<uint16_t>(HorseDrawer::AnimationType::eIdle),
		HorseAnimationConfig::kIdleFrame
	);
}

void Horse::Update()
{
	IPet::Update();

	// ���n�����u��
	if ((MapChipCollider::CollisionBit() & ChipCollisionBit::kBottom) &&
		(MapChipCollider::CollisionBit() & ChipCollisionBit::kElderBottom) == 0)
	{
		// ���n�A�j���[�V����
		drawer_->PlayAnimation(
			static_cast<uint16_t>(HorseDrawer::AnimationType::eLanding),
			HorseAnimationConfig::kLandingFrame
		);
	}
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

void Horse::Hit()
{
	IPet::Hit();

	// ��e�A�j���[�V����
	drawer_->PlayAnimation(
		static_cast<uint16_t>(HorseDrawer::AnimationType::eHit),
		HorseAnimationConfig::Hit::kFrame
	);
}

void Horse::Jump(const bool isJumpCount)
{
	IPet::Jump(isJumpCount);

	if (isJumpCount && jumpCounter_ >= maxJumpCount_) { return; }

	// �W�����v�A�j���[�V����
	drawer_->PlayAnimation(
		static_cast<uint16_t>(HorseDrawer::AnimationType::eJump),
		HorseAnimationConfig::kJumpFrame
	);
}

void Horse::Attack()
{
	// �U���V�K����
	SnortAttack* newAttack = new SnortAttack();

	newAttack->Initialize(
		SnortAttackConfig::kAliveTime,
		transform_->pos_,
		SnortAttackConfig::kAcceleration,
		SnortAttackConfig::kMaxSpeed,
		SnortAttackConfig::kRadius,
		SnortAttackConfig::kPower
	);

	CharacterManager::GetInstance()->PushBack(newAttack);

	// �U���A�j���[�V����
	drawer_->PlayAnimation(
		static_cast<uint16_t>(HorseDrawer::AnimationType::eAttack),
		HorseAnimationConfig::kAttackFrame
	);
}
