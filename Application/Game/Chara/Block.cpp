#include "Block.h"
#include "BlockDrawer.h"
#include "Box2DCollider.h"
#include "MathVector.h"

using YGame::Block;

void Block::Initialize(const Transform::Status& status, GameObject* pParent)
{
	GameObject::Initialize("Block", status, pParent);
	
	SetCollider(new GameCollider());
	SetDrawer(BlockDrawer::Create(nullptr, 2));

	{
		collider_->PushBack(
			AttributeType::eBlock, AttributeType::eAll,
			new YMath::Box2DCollider(&transform_->pos_, YMath::ConvertToVector2(transform_->scale_), {}, false));
	}

}

void Block::UpdateBeforeCollision()
{
	GameObject::UpdateBeforeCollision();
}

void Block::UpdateAfterCollision()
{
	GameObject::UpdateAfterCollision();
}
