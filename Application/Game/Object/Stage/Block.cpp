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

std::unique_ptr<Block> Block::Create(const Transform::Status& status, const WorldKey key, const bool isBackground)
{
	std::unique_ptr<Block> newObj = std::make_unique<Block>();

	newObj->Initialize(status, key, isBackground);

	return std::move(newObj);
}

void Block::Initialize(const Transform::Status& status, const WorldKey key, const bool isBackground)
{
	if (isBackground == false)
	{
		BaseStageObject::Initialize("Block", key, status);
	}
	else
	{
		BaseStageObject::Initialize("Block_B", key, status);
	}
	
	if (key == WorldKey::eJourneyKey)
	{
		SetDrawKeys({});
	}
	
	if (isBackground == false)
	{
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
	}

	// 描画
	{
		BlockDrawer::Type type = BlockDrawer::Type::eGreen;
		if (key == WorldKey::eFeverKey)
		{
			type = BlockDrawer::Type::ePurple;
		}
		std::unique_ptr<BlockDrawer> drawer = 
			BlockDrawer::Create({ nullptr, nullptr, "Game", 2 }, type, isBackground);
		drawer->SetParentPosMatPointer(&posMat_);
		drawer->SetWorldKey(worldKey_);
		SetDrawer(std::move(drawer));
	}
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

YGame::ICollisionInfomation Block::GetCollisionInfomation()
{
	ICollisionInfomation result = BaseStageObject::GetCollisionInfomation();

	result.attribute = AttributeType::eBlock;
	result.radius = 0.0f;

	return result;
}
