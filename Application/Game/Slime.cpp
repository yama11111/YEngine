#include "Slime.h"
#include "SlimeDrawer.h"
#include "SphereCollider.h"
#include "MapChipCollisionBitConfig.h"

#include "CharacterConfig.h"
#include "AnimationConfig.h"

#include "Def.h"
#include <cassert>

using YGame::Slime;
using YMath::Vector3;

void Slime::Initialize(const Transform::Status& status)
{
	// ゲームキャラクター初期化
	ICharacter::Initialize(
		"Slime",
		status,
		SlimeConfig::kAcceleration, SlimeConfig::kMaxSpeed,
		SlimeConfig::kHP, SlimeConfig::kAttack, SlimeConfig::kInvincibleTime,
		new SphereCollider({}, AttributeType::eEnemy, AttributeType::eAll, SlimeConfig::kRadius),
		new SlimeDrawer(DrawLocation::eCenter));

	transform_->rota_ = Vector3(0.0f, -PI, 0.0f);

	// 立ちアニメーション
	drawer_->PlayAnimation(
		static_cast<uint16_t>(SlimeDrawer::AnimationType::eIdle),
		SlimeAnimationConfig::kIdleFrame
	);
}

void Slime::Update()
{
	IEnemy::Update();
	
	// 着地した瞬間
	if ((MapChipCollider::CollisionBit() & ChipCollisionBit::kBottom) &&
		(MapChipCollider::CollisionBit() & ChipCollisionBit::kElderBottom) == 0)
	{
		// 着地アニメーション
		drawer_->PlayAnimation(
			static_cast<uint16_t>(SlimeDrawer::AnimationType::eLanding),
			SlimeAnimationConfig::kLandingFrame
		);
	}
}

void Slime::Draw()
{
	IEnemy::Draw();
}

YGame::ICharacter::CollisionInfo Slime::GetCollisionInfo()
{
	CollisionInfo result;

	result.attribute_ = collider_->Attribute();
	result.pos_ = transform_->pos_;
	result.radius_ = SlimeConfig::kRadius;
	result.pStatus_ = &status_;
	result.pSelf_ = this;

	return result;
}

void Slime::Hit()
{
	IEnemy::Hit();

	// 被弾アニメーション
	drawer_->PlayAnimation(
		static_cast<uint16_t>(SlimeDrawer::AnimationType::eHit),
		SlimeAnimationConfig::Hit::kFrame
	);
}
