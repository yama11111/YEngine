#include "Slime.h"
#include "SlimeDrawer.h"
#include "CollisionConfig.h"
#include <cassert>

using YGame::Slime;
using YMath::Vector3;

static const float Radius = 1.0f;
static const Vector3 Acceleration = { 0.1f,1.0f,0.0f };
static const Vector3 MaxSpeed = { 0.3f,1.0f,0.0f };
static const uint32_t HP = 1;
static const uint32_t Attack = 20;
static const uint32_t InvincibleTime = 10;

void Slime::Initialize(const Transform::Status& status)
{
	// ゲームキャラクター初期化
	IGameCharacter::Initialize(
		Attribute::kEnemy, Attribute::kPlayer,
		status,
		Radius,
		Acceleration, MaxSpeed,
		HP, Attack, InvincibleTime,
		new SlimeDrawer(), DrawLocation::eCenter);
}

void Slime::Update()
{
	IEnemy::Update();
}

void Slime::Draw()
{
	IEnemy::Draw();
}
