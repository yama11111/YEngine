#include "IGameCharacter.h"
#include "MapChipManager.h"

using YGame::IGameCharacter;
using YMath::Vector3;

void IGameCharacter::Initialize(
	const uint32_t attribute, const uint32_t mask,
	const Transform::Status& status, 
	const float radius, 
	const Vector3& acceleration, const Vector3& maxSpeed, 
	const uint32_t hp, const uint32_t attack, const uint32_t invincibleTime, 
	IDrawer* drawer, const DrawLocation location)
{
	// オブジェクト初期化
	IGameObject::Initialize(status, drawer, location);

	// コライダー更新
	BaseCollider::Initialize(attribute, mask, &transform_->pos_, radius);

	// マップチップコライダー初期化
	MapChipCollider::Initialize(status.scale_);

	// スピード初期化
	speed_.Initialize(acceleration, maxSpeed);

	// キャラステータス初期化
	status_.Initialize(hp, attack, invincibleTime);
}

void IGameCharacter::Update()
{
	// スピード更新
	speed_.Update(moveDirection_);

	// 移動方向初期化
	moveDirection_ = Vector3();

	// マップチップとのアタリ判定
	MapChipManager::GetInstance()->CurrentMapPointer()->PerfectPixelCollision(*this);

	// 位置にスピード加算
	transform_->pos_ += speed_.Velocity();

	// オブジェクト更新
	IGameObject::Update();

	// コライダー更新
	BaseCollider::Update();

	// キャラステータス更新
	status_.Update();
}

bool IGameCharacter::IsAlive() const
{
	return status_.IsAlive();
}

YGame::CharacterStatus IGameCharacter::Status() const
{
	return status_;
}

Vector3& IGameCharacter::PosRef()
{
	return transform_->pos_;
}

Vector3& IGameCharacter::SpeedRef()
{
	return speed_.VelocityRef();
}
