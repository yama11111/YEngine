#include "Coin.h"
#include "CharacterConfig.h"
#include "ScoreManager.h"
#include "CoinDrawer.h"

#include "PrimitiveCollider.h"
#include "MapChipCollisionBitConfig.h"
#include "CollisionDrawer.h"

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
		new GameCollider(transform_.get(), AttributeType::eItem, AttributeType::eAll),
		CoinDrawer::Create(nullptr, 1));

	collider_->PushBack(new YMath::SphereCollider(Vector3(), CoinConfig::kRadius));
	
	InsertSubDrawer(CollisionDrawer::Name(), CollisionDrawer::Create(transform_.get(), CoinConfig::kRadius, 1));
	drawer_->PlayAnimation(static_cast<uint32_t>(CoinDrawer::AnimationType::eIdle), true);

	drawer_->SetParent(transform_.get());
}

void Coin::Update(const bool isUpdate)
{
	BaseCharacter::Update(isUpdate);

	if (status_.IsInvincible() && 
		drawer_->IsActAnimation(static_cast<uint32_t>(CoinDrawer::AnimationType::eEarn)) == false)
	{
		status_.SetHP(0);
	}
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

YGame::BaseCharacter::CollisionInfo Coin::GetCollisionInfo()
{
	CollisionInfo result;

	result.attribute = collider_->Attribute();
	result.pos		 = transform_->pos_;
	result.radius	 = 0.0f;
	result.pStatus	 = &status_;
	result.pSelf	 = this;

	return result;
}