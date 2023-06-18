#include "Slime.h"
#include "SlimeDrawer.h"

using YGame::Slime;
using YMath::Vector3;

static const float Radius = 0.0f;
static const Vector3 Acceleration = { 0.1f,1.0f,0.0f };
static const Vector3 MaxSpeed = { 0.3f,1.0f,0.0f };
static const uint16_t MaxJumpCount = 1;
static const uint32_t HP = 1;
static const uint32_t Attack = 20;

void Slime::Initialize(const Transform::Status& status)
{
	// ゲームキャラクター初期化
	IGameCharacter::Initialize(
		GameObjectCollider::Type::eEnemy,
		status,
		Radius,
		Acceleration, MaxSpeed,
		MaxJumpCount,
		HP, Attack,
		new SlimeDrawer());
}

void Slime::Update()
{
	IEnemy::Update();
}

void Slime::Draw()
{
	IEnemy::Draw();
}
