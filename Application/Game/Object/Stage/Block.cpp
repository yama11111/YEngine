#include "Block.h"
#include "BlockDrawer.h"
#include "Box2DCollider.h"
#include "MathVector.h"

using YGame::Block;
using YMath::BitFrag;

std::unique_ptr<Block> Block::Create(const Transform::Status& status, GameObject* pParent)
{
	std::unique_ptr<Block> newObj = std::make_unique<Block>();

	newObj->Initialize(status, pParent);

	return std::move(newObj);
}

void Block::Initialize(const Transform::Status& status, GameObject* pParent)
{
	GameObject::Initialize("Block", status, pParent);
	
	BitFrag attribute{};
	attribute.SetFragTrue(AttributeType::eBlock);

	SetCollider(GameCollider::Create(attribute));

	BitFrag mask{};
	mask.SetFragTrue(AttributeType::ePlayer);
	mask.SetFragTrue(AttributeType::ePet);
	mask.SetFragTrue(AttributeType::eEnemy);

	collider_->PushBackCollider(
		std::make_unique<YMath::Box2DCollider>(
			&transform_->pos_, YMath::ConvertToVector2(transform_->scale_)), mask);

	SetDrawer(BlockDrawer::Create(nullptr, false, 2));
}

void Block::UpdateBeforeCollision()
{
	GameObject::UpdateBeforeCollision();
}

void Block::UpdateAfterCollision()
{
	GameObject::UpdateAfterCollision();
}

YGame::InfoOnCollision Block::GetInfoOnCollision()
{
	InfoOnCollision result;

	result.attribute = AttributeType::eBlock;
	result.pTrfm = transform_.get();
	result.radius = 0.0f;
	result.pStatus = nullptr;

	return result;
}
