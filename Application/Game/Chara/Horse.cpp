#include "Horse.h"
#include "HorseDrawer.h"
#include "CharacterConfig.h"
#include "AnimationConfig.h"
#include "CharacterManager.h"
#include "SnortAttack.h"

#include "CollisionDrawer.h"
#include "PrimitiveCollider.h"
#include "MapChipCollisionBitConfig.h"

#include <cassert>

using YGame::Horse;
using YMath::Vector3;

void Horse::Initialize(const Transform::Status& status)
{
	BaseCharacter::Initialize(
		"Horse",
		status,
		{ +1.0f, 0.0f, 0.0f }, // 右向き
		PetConfig::kNormalAcceleration, PetConfig::kNormalMaxSpeed,
		PetConfig::kHP, PetConfig::kAttack, PetConfig::kInvincibleTime,
		new GameCollider(transform_.get(), AttributeType::ePet, AttributeType::eAll),
		HorseDrawer::Create(nullptr, 1));

	collider_->PushBack(new YMath::SphereCollider(Vector3(), PetConfig::kRadius));

	InsertSubDrawer(CollisionDrawer::Name(), CollisionDrawer::Create(transform_.get(), PetConfig::kRadius, 1));

	isHit_ = false;

	jumpCounter_ = 0;

	maxJumpCount_ = PetConfig::kMaxJumpCount;

	// 立ちアニメーション
	drawer_->PlayAnimation(
		static_cast<uint16_t>(HorseDrawer::AnimationType::eIdle),
		HorseAnimationConfig::kIdleFrame
	);

	// 移動アニメーション
	drawer_->PlayAnimation(
		static_cast<uint16_t>(HorseDrawer::AnimationType::eMove), 
		HorseAnimationConfig::Move::kFrame, 
		true
	);
}

void Horse::Update(const bool isUpdate)
{
	IPet::Update(isUpdate);

	// 着地した瞬間
	if ((MapChipCollider::CollisionBit() & ChipCollisionBit::kBottom) &&
		(MapChipCollider::CollisionBit() & ChipCollisionBit::kElderBottom) == 0)
	{
		// 着地アニメーション
		drawer_->PlayAnimation(
			static_cast<uint16_t>(HorseDrawer::AnimationType::eLanding),
			HorseAnimationConfig::Landing::kFrame
		);
	}
}

YGame::BaseCharacter::CollisionInfo Horse::GetCollisionInfo()
{
	CollisionInfo result;

	result.attribute_ = collider_->Attribute();
	result.pos_ = transform_->pos_;
	result.radius_ = PetConfig::kRadius;
	result.pStatus_ = &status_;
	result.pSelf_ = this;

	return result;
}

YMath::Vector3 Horse::RidingPosHeight()
{
	return PetConfig::kRiddenHeight;
}

void Horse::Hit()
{
	IPet::Hit();

	// 被弾アニメーション
	drawer_->PlayAnimation(
		static_cast<uint16_t>(HorseDrawer::AnimationType::eHit),
		HorseAnimationConfig::Hit::kFrame
	);
}

void Horse::Jump(const bool isJumpCount)
{
	IPet::Jump(isJumpCount);

	if (isJumpCount && jumpCounter_ >= maxJumpCount_) { return; }

	// ジャンプアニメーション
	drawer_->PlayAnimation(
		static_cast<uint16_t>(HorseDrawer::AnimationType::eJump),
		HorseAnimationConfig::Jump::kFrame
	);
}

void Horse::Attack()
{
	// 攻撃新規生成
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

	// 攻撃アニメーション
	drawer_->PlayAnimation(
		static_cast<uint16_t>(HorseDrawer::AnimationType::eAttack),
		HorseAnimationConfig::kAttackFrame
	);
}

void Horse::Rideen()
{
	IPet::Rideen();
}

void Horse::GotOff()
{
	IPet::GotOff();
}
