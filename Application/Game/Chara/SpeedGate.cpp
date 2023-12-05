#include "SpeedGate.h"
#include "GateDrawer.h"
#include "Box2DCollider.h"
#include "MathVector.h"

using YGame::SpeedGate;

std::unique_ptr<SpeedGate> SpeedGate::Create(const Transform::Status& status, GameObject* pParent)
{
	std::unique_ptr<SpeedGate> newObj = std::make_unique<SpeedGate>();

	newObj->Initialize(status, pParent);

	return std::move(newObj);
}

void SpeedGate::Initialize(const Transform::Status& status, GameObject* pParent)
{
	GameObject::Initialize("SpeedGate", status, pParent);

	Attribute attribute{};
	attribute.Add(AttributeType::eGate);

	SetCollider(GameCollider::Create(attribute));

	Attribute mask{};
	mask.Add(AttributeType::ePlayer);
	mask.Add(AttributeType::ePet);

	collider_->PushBackCollider(
		std::make_unique<YMath::Box2DCollider>(
			&transform_->pos_, YMath::ConvertToVector2(transform_->scale_)), mask);

	SetDrawer(GateDrawer::Create(nullptr, 2));
}

void SpeedGate::UpdateBeforeCollision()
{
	GameObject::UpdateBeforeCollision();
}

void SpeedGate::UpdateAfterCollision()
{
	GameObject::UpdateAfterCollision();
}

YGame::InfoOnCollision SpeedGate::GetInfoOnCollision()
{
	InfoOnCollision result;

	result.attribute = AttributeType::eGate;
	result.pTrfm = transform_.get();
	result.radius = 0.0f;
	result.pStatus = nullptr;

	return result;
}