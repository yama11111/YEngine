#include "Block.h"
#include "BlockDrawer.h"
#include "Box2DCollider.h"
#include "MathVector.h"
#include "WorldManager.h"

using YGame::WorldManager;
using YGame::Block;
using YMath::BitFrag;

namespace
{
	WorldManager* pWorldMan = WorldManager::GetInstance();
}

std::unique_ptr<Block> Block::Create(
	const Transform::Status& status,
	const std::vector<std::string>& drawKeys, 
	GameObject* pParent)
{
	std::unique_ptr<Block> newObj = std::make_unique<Block>();

	newObj->Initialize(status, pParent);
	newObj->SetDrawKeys(drawKeys);

	return std::move(newObj);
}

void Block::Initialize(const Transform::Status& status, GameObject* pParent)
{
	GameObject::Initialize("Block", status, pParent);
	
	BitFrag attribute{};
	attribute.SetFragTrue(AttributeType::eBlock);

	SetCollider(GameCollider::Create(attribute));

	SetIsSaveColl(true);
	
	{
		BitFrag mask{};
		mask.SetFragTrue(AttributeType::ePlayer);
		mask.SetFragTrue(AttributeType::eEnemy);

		collider_->PushBackCollider(
			std::make_unique<YMath::Box2DCollider>(
				&worldPos_, YMath::ConvertToVector2(transform_->scale_)), mask);
	}

	SetDrawer(BlockDrawer::Create(nullptr, nullptr, false, 2));
}

void Block::UpdateBeforeCollision()
{
	GameObject::UpdateBeforeCollision();
}

void Block::UpdateAfterCollision()
{
	UpdatePos();

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
