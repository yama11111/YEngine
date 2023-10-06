#include "Coin.h"
#include "ScoreManager.h"

using YGame::Coin;

void Coin::Initialize(const Transform::Status& status)
{

}

void Coin::Update(const bool isUpdate)
{

}

void Coin::OnCollision(const CollisionInfo& info)
{
	if (info.attribute_ == AttributeType::ePlayer)
	{
		//ScoreManager::
	}
}
