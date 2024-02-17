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

std::unique_ptr<Goal> Goal::Create(const Transform::Status& status, const std::string& key)
{
	std::unique_ptr<Goal> newObj = std::make_unique<Goal>();

	newObj->Initialize(status, key);

	return std::move(newObj);
}

void Goal::Initialize(const Transform::Status& status, const std::string& key)
{
	GameObject::Initialize("Goal", status, nullptr);

	SetUpdateKey(key);
	SetDrawKeys({ key });

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

	SetDrawer(GoalDrawer::Create({ nullptr, nullptr, key, 2 }));
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
	ICollisionInfomation result;

	result.attribute = AttributeType::eGoal;
	result.pTrfm = transform_.get();
	result.radius = 0.0f;
	result.pStatus = nullptr;

	return result;
}
