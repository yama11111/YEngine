#include "Slime.h"
#include "SlimeDrawer.h"
#include "CharacterConfig.h"
#include "AnimationConfig.h"

#include "CollisionDrawer.h"
#include "PrimitiveCollider.h"
#include "MapChipCollisionBitConfig.h"

#include "Def.h"
#include <cassert>

using YGame::Slime;
using YMath::Vector3;

void Slime::Initialize(const Transform::Status& status)
{
	// ゲームキャラクター初期化
	BaseCharacter::Initialize(
		"Slime",
		status,
		{ -1.0f, 0.0f, 0.0f }, // 左向き
		SlimeConfig::kAcceleration, SlimeConfig::kMaxSpeed,
		SlimeConfig::kHP, SlimeConfig::kAttack, SlimeConfig::kInvincibleTime,
		new GameCollider(transform_.get(), AttributeType::eEnemy, AttributeType::eAll),
		SlimeDrawer::Create(nullptr, 1));

	collider_->PushBack(new YMath::SphereCollider(Vector3(), SlimeConfig::kRadius));

	InsertSubDrawer(CollisionDrawer::Name(), CollisionDrawer::Create(transform_.get(), SlimeConfig::kRadius, 1));

	// 立ちアニメーション
	drawer_->PlayAnimation(static_cast<uint32_t>(SlimeDrawer::AnimationType::eIdle), true);
}

void Slime::Update(const bool isUpdate)
{
	BaseCharacter::Update(isUpdate);
	
	// 着地した瞬間
	if ((MapChipCollider::CollisionBit() & ChipCollisionBit::kBottom) &&
		(MapChipCollider::CollisionBit() & ChipCollisionBit::kElderBottom) == 0)
	{
		// 着地アニメーション
		drawer_->PlayAnimation(static_cast<uint32_t>(SlimeDrawer::AnimationType::eLanding), true);
	}
}

YGame::BaseCharacter::CollisionInfo Slime::GetCollisionInfo()
{
	CollisionInfo result;

	result.attribute = collider_->Attribute();
	result.pos		 = transform_->pos_;
	result.radius	 = SlimeConfig::kRadius;
	result.pStatus	 = &status_;
	result.pSelf	 = this;

	return result;
}

void Slime::Hit()
{
	IEnemy::Hit();

	// 被弾アニメーション
	drawer_->PlayAnimation(static_cast<uint32_t>(SlimeDrawer::AnimationType::eHit), true);

	if (status_.IsAlive() == false)
	{
		// 死亡アニメーション
		drawer_->PlayAnimation(static_cast<uint32_t>(SlimeDrawer::AnimationType::eDead), true);
	}
}
