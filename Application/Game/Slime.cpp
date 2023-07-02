#include "Slime.h"
#include "SlimeDrawer.h"
#include "SphereCollider.h"

#include "CharacterConfig.h"

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
}

void Slime::Update()
{
	IEnemy::Update();
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
