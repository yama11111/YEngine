#include "Goal.h"
#include "GoalDrawer.h"
#include "Box2DCollider.h"
#include "SphereCollider.h"
#include "MathVector.h"

using YGame::Goal;
using YMath::BasePrimitiveCollider;

std::unique_ptr<Goal> Goal::Create(const Transform::Status& status, GameObject* pParent)
{
	std::unique_ptr<Goal> newObj = std::make_unique<Goal>();

	newObj->Initialize(status, pParent);

	return std::move(newObj);
}

void Goal::Initialize(const Transform::Status& status, GameObject* pParent)
{
	GameObject::Initialize("Goal", status, pParent);

	Attribute attribute{};
	attribute.Add(AttributeType::eGoal);

	SetCollider(GameCollider::Create(attribute));
	
	{
		Attribute mask{};
		mask.Add(AttributeType::ePlayer);
		mask.Add(AttributeType::ePet);

		collider_->PushBackCollider(
			std::make_unique<YMath::Box2DCollider>(
				&transform_->pos_, YMath::ConvertToVector2(transform_->scale_)),
			mask);
	}

	SetDrawer(GoalDrawer::Create(nullptr, 2));
}

void Goal::UpdateBeforeCollision()
{
	GameObject::UpdateBeforeCollision();
}

void Goal::UpdateAfterCollision()
{
	GameObject::UpdateAfterCollision();
}

YGame::InfoOnCollision Goal::GetInfoOnCollision()
{
	InfoOnCollision result;

	result.attribute = AttributeType::eGoal;
	result.pTrfm = transform_.get();
	result.radius = 0.0f;
	result.pStatus = nullptr;

	return result;
}
