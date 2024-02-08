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

std::unique_ptr<Block> Block::Create(const Transform::Status& status, const std::string& key, const bool isBackground)
{
	std::unique_ptr<Block> newObj = std::make_unique<Block>();

	newObj->Initialize(status, key, isBackground);

	return std::move(newObj);
}

void Block::Initialize(const Transform::Status& status, const std::string& key, const bool isBackground)
{
	if (isBackground == false)
	{
		GameObject::Initialize("Block", status, nullptr);
	}
	else
	{
		GameObject::Initialize("Block_B", status, nullptr);
	}

	SetUpdateKey(key);
	SetDrawKeys({ key });
	
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

	SetDrawer(BlockDrawer::Create({ nullptr, nullptr, key, 2 }, isBackground));
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
