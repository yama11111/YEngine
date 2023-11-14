#include "Slime.h"
#include "SlimeDrawer.h"
#include "CharacterConfig.h"
#include "AnimationConfig.h"

#include "CollisionDrawer.h"
#include "SphereCollider.h"
#include "Box2DCollider.h"
#include "CollisionInfo.h"
#include "MapChipCollisionBitConfig.h"

#include "ScoreManager.h"

#include "Def.h"
#include <cassert>

using YGame::Slime;
using YMath::Vector2;
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
		SlimeDrawer::Create(nullptr, 1));

	{
		attribute_ = AttributeType::eEnemy;

		collider_->PushBack(
			attribute_, AttributeType::eBlock,
			new YMath::Box2DCollider(&transform_->pos_, speed_.VelocityPtr(), SlimeConfig::kRectSize, {}, true));

		collider_->PushBack(
			attribute_, AttributeType::eAll,
			new YMath::SphereCollider(&transform_->pos_, speed_.VelocityPtr(), SlimeConfig::kRadius, {}, false));

		collider_->SetPriority(1);
	}

	//InsertSubDrawer(CollisionDrawer::Name(), CollisionDrawer::Create(transform_.get(), SlimeConfig::kRadius, 1));

	blowTim_.Initialize(SlimeConfig::kBlowTime);

	// 立ちアニメーション
	drawer_->PlayAnimation(static_cast<uint32_t>(SlimeDrawer::AnimationType::eIdle), true);
}

void Slime::UpdateBeforeCollision()
{
	IEnemy::UpdateBeforeCollision();
}

void Slime::UpdateAfterCollision()
{	
	IEnemy::UpdateAfterCollision();
	
	// 着地した瞬間
	//if ()
	//{
	//	// 着地アニメーション
	//	drawer_->PlayAnimation(static_cast<uint32_t>(SlimeDrawer::AnimationType::eLanding), true);
	//}
}

YGame::CollisionInfo Slime::GetCollisionInfo()
{
	CollisionInfo result;

	result.attribute = attribute_;
	result.pos = transform_->pos_;
	result.radius = SlimeConfig::kRadius;
	result.pStatus = &status_;
	result.pSelf = this;

	return result;
}

void Slime::Hit(const uint32_t damage, const bool isStepOn)
{
	// 被弾アニメーション
	static_cast<SlimeDrawer*>(drawer_.get())->PlayHitAnimation(damage, isStepOn);

	if (status_.IsAlive() == false)
	{
		// 死亡アニメーション
		drawer_->PlayAnimation(static_cast<uint32_t>(SlimeDrawer::AnimationType::eDead), true);
		ScoreManager::GetInstance()->AddScore(1000);
	}
}
