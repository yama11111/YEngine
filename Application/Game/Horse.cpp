#include "Horse.h"
#include "HorseDrawer.h"
#include "SphereCollider.h"
#include "CollisionConfig.h"
#include <cassert>

using YGame::Horse;
using YMath::Vector3;

static const float Radius = 1.0f;
static const Vector3 Acceleration = { 0.1f,1.0f,0.0f };
static const Vector3 MaxSpeed = { 0.3f,1.0f,0.0f };
static const uint32_t HP = 1;
static const uint32_t Attack = 20;
static const uint32_t InvincibleTime = 10;

void Horse::Initialize(const Transform::Status& status)
{
	// ゲームキャラクター初期化
	ICharacter::Initialize(
		status,
		Acceleration, MaxSpeed,
		HP, Attack, InvincibleTime,
		new SphereCollider({}, Attribute::kPlayer, Attribute::kPlayer, Radius),
		new HorseDrawer(DrawLocation::eCenter));
}

void Horse::Update()
{

}

void Horse::Draw()
{

}
