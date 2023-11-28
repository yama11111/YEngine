#include "Block.h"
#include "BlockDrawer.h"
#include "Box2DCollider.h"
#include "MathVector.h"

using YGame::Block;

std::unique_ptr<Block> Block::Create(const Transform::Status& status, GameObject* pParent)
{
	std::unique_ptr<Block> newObj = std::make_unique<Block>();

	newObj->Initialize(status, pParent);

	return std::move(newObj);
}

void Block::Initialize(const Transform::Status& status, GameObject* pParent)
{
	GameObject::Initialize("Block", status, pParent);
	
	Attribute attribute{};
	attribute.Add(AttributeType::eBlock);

	SetCollider(GameCollider::Create(attribute));

	Attribute mask{};
	mask.Add(AttributeType::ePlayer);
	mask.Add(AttributeType::ePet);
	mask.Add(AttributeType::eEnemy);

	collider_->PushBackCollider(
		std::make_unique<YMath::Box2DCollider>(
			&transform_->pos_, YMath::ConvertToVector2(transform_->scale_)), mask);

	SetDrawer(BlockDrawer::Create(nullptr, 2));
}

void Block::UpdateBeforeCollision()
{
	GameObject::UpdateBeforeCollision();
}

void Block::UpdateAfterCollision()
{
	GameObject::UpdateAfterCollision();
}
