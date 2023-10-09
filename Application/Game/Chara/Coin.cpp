#include "Coin.h"
#include "ScoreManager.h"
#include "PlayerDrawer.h"

using YGame::Coin;

void Coin::Initialize(const Transform::Status& status)
{
	BaseCharacter::Initialize(
		"Coin",
		status,
		{ +1.0f, 0.0f, 0.0f }, // 右向き
		{}, {}, {}, {}, 0,
		new GameCollider(transform_.get(), AttributeType::ePlayer, AttributeType::eAll),
		PlayerDrawer::Create(nullptr, 1));
}

void Coin::Update(const bool isUpdate)
{
	BaseCharacter::Update(isUpdate);
}

void Coin::OnCollision(const CollisionInfo& info)
{
	if (info.attribute_ == AttributeType::ePlayer)
	{
		//ScoreManager::
	}
}
