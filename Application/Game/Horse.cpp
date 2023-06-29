#include "Horse.h"
#include "HorseDrawer.h"
#include "SphereCollider.h"
#include <cassert>

using YGame::Horse;
using YMath::Vector3;

static const float kRadius = 1.0f;
static const Vector3 kAcceleration = { 0.1f,1.0f,0.0f };
static const Vector3 kMaxSpeed = { 0.3f,1.0f,0.0f };
static const uint32_t kHP = 1;
static const uint32_t kAttack = 20;
static const uint32_t kInvincibleTime = 10;

void Horse::Initialize(const Transform::Status& status)
{
	// ゲームキャラクター初期化
	ICharacter::Initialize(
		"Horse",
		status,
		kAcceleration, kMaxSpeed,
		kHP, kAttack, kInvincibleTime,
		new SphereCollider({}, AttributeType::ePlayer, AttributeType::ePlayer, kRadius),
		new HorseDrawer(DrawLocation::eCenter));
}

void Horse::Update()
{

}

void Horse::Draw()
{

}

inline YGame::ICharacter::CollisionInfo Horse::GetCollisionInfo()
{
	return CollisionInfo();
}
