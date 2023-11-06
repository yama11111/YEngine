#include "Horse.h"
#include "HorseDrawer.h"
#include "CharacterConfig.h"
#include "AnimationConfig.h"
#include "CharacterManager.h"
#include "NeedleAttack.h"

#include "CollisionDrawer.h"
#include "PrimitiveCollider.h"
#include "MapChipCollisionBitConfig.h"

#include <cassert>

using YGame::Horse;
using YMath::Vector2;
using YMath::Vector3;

void Horse::Initialize(const Transform::Status& status)
{
	BaseCharacter::Initialize(
		"Horse",
		status,
		{ +1.0f, 0.0f, 0.0f }, // 右向き
		PetConfig::kNormalAcceleration, PetConfig::kNormalMaxSpeed,
		PetConfig::kHP, PetConfig::kAttack, PetConfig::kInvincibleTime,
		HorseDrawer::Create(nullptr, 1));

	transform_->Initialize();

	{
		attribute_ = AttributeType::ePet;

		collider_->PushBack(
			attribute_, AttributeType::eBlock,
			new YMath::Box2DCollider(&transform_->pos_, speed_.VelocityPtr(), PetConfig::kRectSize, {}, true));

		collider_->PushBack(
			attribute_, AttributeType::eAll,
			new YMath::SphereCollider(&transform_->pos_, PetConfig::kRadius));
	}

	InsertSubDrawer(CollisionDrawer::Name(), CollisionDrawer::Create(transform_.get(), PetConfig::kRadius, 1));

	isHit_ = false;

	jumpCounter_ = 0;

	maxJumpCount_ = PetConfig::kMaxJumpCount;

	// 立ちアニメーション
	drawer_->PlayAnimation(static_cast<uint32_t>(HorseDrawer::AnimationType::eIdle), true);

	// 移動アニメーション
	drawer_->PlayAnimation(static_cast<uint32_t>(HorseDrawer::AnimationType::eMove), true);
}

void Horse::Update(const bool isUpdate)
{
	IPet::Update(isUpdate);

	// 着地した瞬間
	if ((MapChipCollider::CollisionBit() & ChipCollisionBit::kBottom) &&
		(MapChipCollider::CollisionBit() & ChipCollisionBit::kElderBottom) == 0)
	{
		// 着地アニメーション
		drawer_->PlayAnimation(static_cast<uint32_t>(HorseDrawer::AnimationType::eLanding), true);
	}
}

YGame::BaseCharacter::CollisionInfo Horse::GetCollisionInfo()
{
	CollisionInfo result;

	result.attribute = attribute_;
	result.pos		 = transform_->pos_;
	result.radius	 = PetConfig::kRadius;
	result.pStatus	 = &status_;
	result.pSelf	 = this;

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
	drawer_->PlayAnimation(static_cast<uint32_t>(HorseDrawer::AnimationType::eHit), true);
}

void Horse::Jump(const bool isJumpCount)
{
	IPet::Jump(isJumpCount);

	if (isJumpCount && jumpCounter_ >= maxJumpCount_) { return; }

	// ジャンプアニメーション
	drawer_->PlayAnimation(static_cast<uint32_t>(HorseDrawer::AnimationType::eJump), true);
}

void Horse::Attack()
{
	// 攻撃新規生成
	NeedleAttack* newAttack = new NeedleAttack();

	newAttack->Initialize(
		NeedleAttackConfig::kAliveTime,
		transform_->pos_ + Vector3(+5.0f, 0.0f, 0.0f),
		NeedleAttackConfig::kAcceleration,
		NeedleAttackConfig::kMaxSpeed,
		NeedleAttackConfig::kRadius,
		NeedleAttackConfig::kPower
	);

	CharacterManager::GetInstance()->PushBack(newAttack);

	// 攻撃アニメーション
	drawer_->PlayAnimation(static_cast<uint32_t>(HorseDrawer::AnimationType::eAttack), true);
}

void Horse::Rideen()
{
	IPet::Rideen();
}

void Horse::GotOff()
{
	IPet::GotOff();
}
