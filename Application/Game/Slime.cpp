#include "Slime.h"
#include "SlimeDrawer.h"
#include "SphereCollider.h"
#include <cassert>

using YGame::Slime;
using YMath::Vector3;

static const float kRadius = 1.0f;
static const Vector3 kAcceleration = { 0.1f,1.0f,0.0f };
static const Vector3 kMaxSpeed = { 0.3f,1.0f,0.0f };
static const uint32_t kHP = 1;
static const uint32_t kAttack = 1;
static const uint32_t kInvincibleTime = 10;

void Slime::Initialize(const Transform::Status& status)
{
	// ゲームキャラクター初期化
	ICharacter::Initialize(
		"Slime",
		status,
		kAcceleration, kMaxSpeed,
		kHP, kAttack, kInvincibleTime,
		new SphereCollider({}, AttributeType::eEnemy, AttributeType::ePlayer, kRadius),
		new SlimeDrawer(DrawLocation::eCenter));
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
	result.radius_ = kRadius;
	result.pStatus_ = &status_;

	return result;
}
