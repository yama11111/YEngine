#include "BaseCharacter.h"

#include "MathVector.h"
#include "MathUtil.h"

#include "CharacterConfig.h"
#include "CollisionInfoQueue.h"

#include <imgui.h>

using YGame::BaseCharacter;
using YMath::Vector3;

namespace 
{
	YGame::CollisionInfoQueue* pCollInfoQueue = nullptr;
}

void BaseCharacter::StaticInitialize()
{
	pCollInfoQueue = CollisionInfoQueue::GetInstance();
}

void BaseCharacter::Initialize(
	const std::string& name,
	const Transform::Status& status,
	const Vector3& direction,
	const Vector3& acceleration, const Vector3& maxSpeed,
	const uint32_t hp, const uint32_t attack, const uint32_t invincibleTime,
	BaseDrawer* drawer)
{
	GameObject::Initialize(name, status);

	direction_ = direction;

	speed_.Initialize(acceleration, maxSpeed);

	status_.Initialize(hp, attack, invincibleTime);

	GameObject::SetCollider(new GameCollider());
	
	GameObject::SetDrawer(drawer);
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

	// 衝突処理
	UpdateCollision();
	
	status_.Update();

	// 画面外なら死ぬ
	if (YMath::InRange(transform_->pos_, -YGame::kMaxWorldSize, YGame::kMaxWorldSize) == false)
	{
		OffScreenProcess();
	}
	
	isExist_ = IsAlive();
}

void BaseCharacter::SendCollisionInfo(const size_t collIndex)
{
	pCollInfoQueue->PushBack(collIndex, GetCollisionInfo());
}

void BaseCharacter::OffScreenProcess()
{
	status_.Damage(1000, false);
}

void BaseCharacter::UpdateCollision()
{
	// 衝突情報を1つ1つ処理
	// 空なら終わり
	while (true)
	{
		if (pCollInfoQueue->Empty(collIndex_)) { break; }

		OnCollision(pCollInfoQueue->Front(collIndex_));

		pCollInfoQueue->Pop(collIndex_);
	}
}

void BaseCharacter::OnCollision(const CollisionInfo& info)
{
	info;
}

void BaseCharacter::DrawDebugTextContent()
{
	status_.DrawDebugTextContent();

	GameObject::DrawDebugTextContent();
}