#include "Horse.h"
#include "HorseDrawer.h"
#include "CharacterConfig.h"
#include "AnimationConfig.h"
#include "GameObjectManager.h"
#include "NeedleAttack.h"

#include "CollisionDrawer.h"
#include "SphereCollider.h"
#include "Box2DCollider.h"
#include "MapChipCollisionBitConfig.h"

#include <cassert>

using YGame::Horse;
using YMath::Vector2;
using YMath::Vector3;
using YMath::BitFrag;

std::unique_ptr<Horse> Horse::Create(const Transform::Status& status)
{
	std::unique_ptr<Horse> newObj = std::make_unique<Horse>();

	newObj->Initialize(status);

	return std::move(newObj);
}

void Horse::Initialize(const Transform::Status& status)
{
	BaseCharacter::Initialize(
		"Horse",
		status,
		{ +1.0f, 0.0f, 0.0f }, // 右向き
		PetConfig::kNormalAcceleration, PetConfig::kNormalMaxSpeed, true,
		PetConfig::kHP, PetConfig::kAttack, PetConfig::kInvincibleTime);

	BitFrag attribute{};
	attribute.SetFragTrue(AttributeType::ePet);
	
	SetCollider(GameCollider::Create(attribute));
	
	{
		BitFrag mask{};
		mask.SetFragTrue(AttributeType::eBlock);

		collider_->PushBackCollider(
			std::make_unique<YMath::Box2DCollider>(
				&transform_->pos_, speed_.VelocityPtr(), PetConfig::kRectSize, Vector3(), true, false),
			mask);
	}

	{
		BitFrag mask{};
		mask.SetFragTrue(AttributeType::eGate);
		mask.SetFragTrue(AttributeType::eGoal);

		collider_->PushBackCollider(
			std::make_unique<YMath::Box2DCollider>(
				&transform_->pos_, PetConfig::kRectSize),
			mask);
	}

	{
		BitFrag mask{};
		mask.SetFragTrue(AttributeType::eEnemy);
		mask.SetFragTrue(AttributeType::eEnemyAttack);

		collider_->PushBackCollider(
			std::make_unique<YMath::Box2DCollider>(
				&transform_->pos_, speed_.VelocityPtr(), PetConfig::kRectSize, Vector3(), false, false),
			mask);
	}
	
	{
		BitFrag mask{};
		mask.SetFragTrue(AttributeType::ePlayer);
		mask.SetFragTrue(AttributeType::eCoin);
		mask.SetFragTrue(AttributeType::eItem);
		
		collider_->PushBackCollider(
			std::make_unique<YMath::SphereCollider>(
				&transform_->pos_, PetConfig::kRadius), 
			mask);
	}

	collider_->SetPriority(1);

	isHit_ = false;

	jumpCounter_ = 0;

	maxJumpCount_ = PetConfig::kMaxJumpCount;
	
	SetDrawer(HorseDrawer::Create(nullptr, 1));

	// 立ちアニメーション
	drawer_->PlayAnimation(static_cast<uint32_t>(HorseDrawer::AnimationType::eIdle), true);

	// 移動アニメーション
	drawer_->PlayAnimation(static_cast<uint32_t>(HorseDrawer::AnimationType::eMove), true);
}

void Horse::UpdateBeforeCollision()
{
	IPet::UpdateBeforeCollision();
}

void Horse::UpdateAfterCollision()
{
	IPet::UpdateAfterCollision();

	// 着地した瞬間
	//if ()
	//{
	//	// 着地アニメーション
	//	drawer_->PlayAnimation(static_cast<uint32_t>(HorseDrawer::AnimationType::eLanding), true);
	//}
}

YGame::InfoOnCollision Horse::GetInfoOnCollision()
{
	InfoOnCollision result = BaseCharacter::GetInfoOnCollision();

	result.attribute = AttributeType::ePet;
	result.radius = PetConfig::kRadius;

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
	GameObjectManager::GetInstance()->PushBack(
		NeedleAttack::Create(
			NeedleAttackConfig::kAliveTime,
			transform_->pos_ + Vector3(+5.0f, 0.0f, 0.0f),
			NeedleAttackConfig::kAcceleration,
			NeedleAttackConfig::kMaxSpeed,
			NeedleAttackConfig::kRadius,
			NeedleAttackConfig::kPower), 0, true, true);

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
