#include "IGameCharacter.h"
#include "Physics.h"
#include "MapChipManager.h"

using YGame::IGameCharacter;
using YMath::Vector3;

void IGameCharacter::Initialize(
	const Type type, 
	const Transform::Status& status, 
	const float radius, 
	const Vector3& acceleration, const Vector3& max, 
	const uint16_t maxJumpCount, 
	const uint32_t hp, const uint32_t attack)
{
	// オブジェクト初期化
	IGameObject::Initialize(type, status, radius);

	// マップチップコライダー初期化
	MapChipCollider::Initialize(status.scale_);

	// スピード初期化
	speed_.Initialize(acceleration, max);

	// 最大ジャンプ回数初期化
	maxJumpCount_ = maxJumpCount;

	// キャラクターステータス初期化
	status_.Initialize(hp, attack);
}

void IGameCharacter::Update()
{
	// スピード更新
	speed_.Update(moveDirection_);

	// 移動方向初期化
	moveDirection_ = Vector3();

	// マップチップとのアタリ判定
	MapChipManager::GetInstance()->CurrentMapPointer()->PerfectPixelCollision(*this);

	// 着地しているなら
	if (isLanding_)
	{
		// ジャンプ回数初期化
		jumpCounter_ = 0;
	}
}

bool IGameCharacter::IsAlive() const
{
	return status_.IsAlive();
}

Vector3& IGameCharacter::PosRef()
{
	return transform_->pos_;
}

Vector3& IGameCharacter::SpeedRef()
{
	return speed_.VelocityRef();
}

void IGameCharacter::Jump()
{
	// ジャンプ回数 が 最大回数超えてたら 弾く
	if (jumpCounter_ >= maxJumpCount_) { return; }

	// y軸 に進む
	moveDirection_.y_ = 1.0f;

	// ジャンプカウント
	jumpCounter_++;
}
