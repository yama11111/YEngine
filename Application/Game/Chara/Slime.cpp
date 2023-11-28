#include "Slime.h"
#include "SlimeDrawer.h"
#include "CharacterConfig.h"
#include "AnimationConfig.h"

#include "CollisionDrawer.h"
#include "SphereCollider.h"
#include "Box2DCollider.h"
#include "MapChipCollisionBitConfig.h"

#include "ScoreManager.h"

#include "Def.h"
#include <cassert>

using YGame::Slime;
using YMath::Vector2;
using YMath::Vector3;

std::unique_ptr<Slime> Slime::Create(const Transform::Status& status)
{
	std::unique_ptr<Slime> newObj = std::make_unique<Slime>();

	newObj->Initialize(status);

	return std::move(newObj);
}

void Slime::Initialize(const Transform::Status& status)
{
	// ゲームキャラクター初期化
	BaseCharacter::Initialize(
		"Slime",
		status,
		{ -1.0f, 0.0f, 0.0f }, // 左向き
		SlimeConfig::kAcceleration, SlimeConfig::kMaxSpeed, true,
		SlimeConfig::kHP, SlimeConfig::kAttack, SlimeConfig::kInvincibleTime);

	Attribute attribute{};
	attribute.Add(AttributeType::eEnemy);

	SetCollider(GameCollider::Create(attribute));
	
	{
		Attribute mask{};
		mask.Add(AttributeType::eBlock);

		collider_->PushBackCollider(
			std::make_unique<YMath::Box2DCollider>(
				&transform_->pos_, speed_.VelocityPtr(), SlimeConfig::kRectSize, Vector3(), true, false),
			mask);
	}

	{
		Attribute mask{};
		mask.Add(AttributeType::ePlayer);
		mask.Add(AttributeType::ePet);

		collider_->PushBackCollider(
			std::make_unique<YMath::SphereCollider>(
				&transform_->pos_, SlimeConfig::kRadius),
			mask);
	}

	collider_->SetPriority(1);

	SetDrawer(SlimeDrawer::Create(nullptr, 1));

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

YGame::InfoOnCollision Slime::GetInfoOnCollision()
{
	InfoOnCollision result = BaseCharacter::GetInfoOnCollision();

	result.attribute = AttributeType::eEnemy;
	result.radius = SlimeConfig::kRadius;

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
