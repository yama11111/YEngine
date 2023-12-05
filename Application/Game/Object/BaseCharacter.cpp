#include "BaseCharacter.h"

#include "MathVector.h"
#include "MathUtil.h"

#include "CharacterConfig.h"

#include <imgui.h>

using YGame::BaseCharacter;
using YMath::Vector3;

void BaseCharacter::Initialize(
	const std::string& name,
	const Transform::Status& status,
	const Vector3& direction,
	const Vector3& acceleration, const Vector3& maxSpeed, const bool isGravity,
	const uint32_t hp, const uint32_t attack, const uint32_t invincibleTime)
{
	GameObject::Initialize(name, status);

	direction_ = direction;

	speed_.Initialize(acceleration, maxSpeed, isGravity);

	status_.Initialize(hp, attack, invincibleTime);
}

void BaseCharacter::UpdateBeforeCollision()
{
	GameObject::UpdateBeforeCollision();
	
	speed_.Update(moveDirection_);

	moveDirection_ = Vector3();
}

void BaseCharacter::UpdateAfterCollision()
{
	transform_->pos_ += speed_.Velocity();

	// 向き調整
	transform_->rota_ = YMath::AdjustAngle(direction_);

	GameObject::UpdateAfterCollision();
	
	status_.Update();

	// 画面外なら死ぬ
	if (YMath::InRange(transform_->pos_, -YGame::kMaxWorldSize, YGame::kMaxWorldSize) == false)
	{
		OffScreenProcess();
	}
	
	isExist_ = IsAlive();
}

YGame::InfoOnCollision BaseCharacter::GetInfoOnCollision()
{
	InfoOnCollision result;

	result.pTrfm = transform_.get();
	result.pMoveDirection_ = &moveDirection_;
	result.pStatus = &status_;

	return result;
}

void BaseCharacter::OffScreenProcess()
{
	status_.Damage(1000, false);
}

void BaseCharacter::DrawDebugTextContent()
{
	status_.DrawDebugTextContent();

	GameObject::DrawDebugTextContent();
}