#include "ICharacter.h"
#include "MapChipManager.h"

using YGame::ICharacter;
using YMath::Vector3;

void ICharacter::Initialize(
	const Transform::Status& status,
	const Vector3& acceleration, const Vector3& maxSpeed,
	const uint32_t hp, const uint32_t attack, const uint32_t invincibleTime,
	BaseCollider* collider, BaseDrawer* drawer)
{
	// オブジェクト初期化
	GameObject::Initialize(status);

	// コライダー設定
	GameObject::SetCollider(collider);
	
	// 描画クラス設定
	GameObject::SetDrawer(drawer);

	// マップチップコライダー初期化
	MapChipCollider::Initialize(status.scale_);

	// スピード初期化
	speed_.Initialize(acceleration, maxSpeed);

	// キャラステータス初期化
	status_.Initialize(hp, attack, invincibleTime);
}

void ICharacter::Update()
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
	GameObject::Update();

	// キャラステータス更新
	status_.Update();
}

bool ICharacter::IsAlive() const
{
	return status_.IsAlive();
}

YGame::CharacterStatus ICharacter::Status() const
{
	return status_;
}

Vector3& ICharacter::PosRef()
{
	return transform_->pos_;
}

Vector3& ICharacter::SpeedRef()
{
	return speed_.VelocityRef();
}
