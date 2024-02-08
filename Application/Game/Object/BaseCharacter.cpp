#include "BaseCharacter.h"

#include "MathVector.h"
#include "MathUtil.h"

#include "CharacterConfig.h"
#include "WorldManager.h"

#include <imgui.h>

using YGame::BaseCharacter;
using YGame::WorldManager;
using YMath::Vector3;

namespace
{
	WorldManager* pWorldMan = WorldManager::GetInstance();
}

void BaseCharacter::Initialize(
	const std::string& name,
	const std::string& worldKey,
	const Transform::Status& status,
	const Vector3& direction,
	const Vector3& acceleration, const Vector3& maxSpeed, const bool isGravity,
	const uint32_t hp, const uint32_t attack, const uint32_t invincibleTime)
{
	GameObject::Initialize(name, status);

	SetWorldKey(worldKey);

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
	// 位置更新
	UpdatePos();

	// 向き調整
	transform_->rota_ = YMath::AdjustAngle(direction_);

	GameObject::UpdateAfterCollision();
	
	status_.Update();

	OffScreenProcess();
	
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

Vector3 BaseCharacter::WorldPos() const
{
	return worldPos_;
}

void BaseCharacter::SetWorldKey(const std::string& worldKey)
{
	worldKey_ = worldKey;

	SetUpdateKey(worldKey);
	SetDrawKeys({ worldKey });

	if (drawer_) { drawer_->SetVPkey(worldKey); }
}

void BaseCharacter::UpdatePos()
{
	localPos_ += speed_.Velocity();

	worldPos_ = initPos_ + localPos_;

	transform_->pos_ = worldPos_;
}

void BaseCharacter::OffScreenProcess()
{
	// 画面外なら死ぬ
	if (YMath::InRange(transform_->pos_, -YGame::kMaxWorldSize, YGame::kMaxWorldSize) == false)
	{
		status_.Damage(1000, false);
	}
}

void BaseCharacter::DrawDebugTextContent()
{
	status_.DrawDebugTextContent();

	GameObject::DrawDebugTextContent();
}