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
		{ +1.0f, 0.0f, 0.0f }, // 右向き
		{}, {}, 0, 0, 0,
		new GameCollider(transform_.get(), AttributeType::eItem, AttributeType::eAll),
		CoinDrawer::Create(nullptr, 1));

	collider_->PushBack(new YMath::SphereCollider(Vector3(), CoinConfig::kRadius));
	
	InsertSubDrawer(CollisionDrawer::Name(), CollisionDrawer::Create(transform_.get(), CoinConfig::kRadius, 1));

	drawer_->SetParent(transform_.get());
}

void Coin::Update(const bool isUpdate)
{
	BaseCharacter::Update(isUpdate);
}

void Coin::OnCollision(const CollisionInfo& info)
{
	if (info.attribute == AttributeType::ePlayer)
	{
		//ScoreManager::
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