#include "Goal.h"
#include "GoalDrawer.h"
#include "Box2DCollider.h"
#include "SphereCollider.h"
#include "MathVector.h"
#include "WorldManager.h"

using YGame::Goal;
using YGame::WorldManager;
using YMath::BitFrag;

namespace
{
	WorldManager* pWorldMan = WorldManager::GetInstance();
}

std::unique_ptr<Goal> Goal::Create(const Transform::Status& status, const WorldKey key)
{
	std::unique_ptr<Goal> newObj = std::make_unique<Goal>();

	newObj->Initialize(status, key);

	return std::move(newObj);
}

void Goal::Initialize(const Transform::Status& status, const WorldKey key)
{
	BaseStageObject::Initialize("Goal", key, status);

	// アタリ判定
	{
		BitFrag attribute{};
		attribute.SetFragTrue(AttributeType::eGoal);

		SetCollider(GameCollider::Create(attribute));

		SetIsSaveColl(true);

		{
			BitFrag mask{};
			mask.SetFragTrue(AttributeType::ePlayer);

			collider_->PushBackCollider(
				std::make_unique<YMath::Box2DCollider>(
					&worldPos_, YMath::ConvertToVector2(transform_->scale_)),
				mask);
		}
	}

	// 描画
	{
		std::unique_ptr<GoalDrawer> drawer = GoalDrawer::Create({ nullptr, nullptr, "Game", 2 });
		drawer->SetParentPosMatPointer(&posMat_);
		drawer->SetWorldKey(worldKey_);
		SetDrawer(std::move(drawer)); 
	}
}

void Goal::UpdateBeforeCollision()
{
	GameObject::UpdateBeforeCollision();
}

void Goal::UpdateAfterCollision()
{
	UpdatePos();

	GameObject::UpdateAfterCollision();
}

YGame::ICollisionInfomation Goal::GetCollisionInfomation()
{
	ICollisionInfomation result = BaseStageObject::GetCollisionInfomation();

	result.attribute = AttributeType::eGoal;
	result.radius = 0.0f;

	return result;
}
