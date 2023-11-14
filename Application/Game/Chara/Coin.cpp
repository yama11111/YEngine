#include "Coin.h"
#include "CharacterConfig.h"
#include "ScoreManager.h"
#include "CoinDrawer.h"

#include "CollisionDrawer.h"
#include "SphereCollider.h"
#include "CollisionInfo.h"

using YGame::Coin;
using YMath::Vector3;

void Coin::Initialize(const Transform::Status& status)
{
	BaseCharacter::Initialize(
		"Coin",
		status,
		{ 0.0f, 0.0f, +1.0f }, // 右向き
		{}, {}, 
		1, 0, 0,
		CoinDrawer::Create(nullptr, 1));

	{
		attribute_ = AttributeType::eItem;

		collider_->PushBack(
			attribute_, AttributeType::eAll,
			new YMath::SphereCollider(&transform_->pos_, speed_.VelocityPtr(), CoinConfig::kRadius, {}, false));
	}
	
	//InsertSubDrawer(CollisionDrawer::Name(), CollisionDrawer::Create(transform_.get(), CoinConfig::kRadius, 1));
	drawer_->PlayAnimation(static_cast<uint32_t>(CoinDrawer::AnimationType::eIdle), true);

	drawer_->SetParent(transform_.get());
}

void Coin::UpdateBeforeCollision()
{
	BaseCharacter::UpdateBeforeCollision();
}

void Coin::UpdateAfterCollision()
{
	BaseCharacter::UpdateAfterCollision();

	if (status_.IsInvincible() && 
		drawer_->IsActAnimation(static_cast<uint32_t>(CoinDrawer::AnimationType::eEarn)) == false)
	{
		status_.SetHP(0);
	}
}

YGame::CollisionInfo Coin::GetCollisionInfo()
{
	CollisionInfo result;

	result.attribute = attribute_;
	result.pos = transform_->pos_;
	result.radius = 0.0f;
	result.pStatus = &status_;
	result.pSelf = this;

	return result;
}

void Coin::OnCollision(const CollisionInfo& info)
{
	if (status_.IsInvincible()) { return; }
	
	if (info.attribute == AttributeType::ePlayer || 
		info.attribute == AttributeType::ePet)
	{
		ScoreManager::GetInstance()->AddScore(100);
		
  		drawer_->PlayAnimation(static_cast<uint32_t>(CoinDrawer::AnimationType::eEarn), true);
		status_.SetInvincible(true);
	}
}