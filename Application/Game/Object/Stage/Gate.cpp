#include "Gate.h"
#include "GateDrawer.h"
#include "Box2DCollider.h"
#include "MathVector.h"
#include "WorldManager.h"

using YGame::Gate;
using YMath::BitFrag;
using YGame::WorldManager;

namespace
{
	WorldManager* pWorldMan = WorldManager::GetInstance();
}

std::unique_ptr<Gate> Gate::Create(
	const Transform::Status& status,
	const std::vector<std::string>& drawKeys, 
	GameObject* pParent)
{
	std::unique_ptr<Gate> newObj = std::make_unique<Gate>();

	newObj->Initialize(status, pParent);
	newObj->SetDrawKeys(drawKeys);

	return std::move(newObj);
}

void Gate::Initialize(const Transform::Status& status, GameObject* pParent)
{
	GameObject::Initialize("Gate", status, pParent);

	BitFrag attribute{};
	attribute.SetFragTrue(AttributeType::eGate);

	SetCollider(GameCollider::Create(attribute));
	
	SetIsSaveColl(true);
	
	{
		BitFrag mask{};
		mask.SetFragTrue(AttributeType::ePlayer);

		collider_->PushBackCollider(
			std::make_unique<YMath::Box2DCollider>(
				&worldPos_, YMath::ConvertToVector2(transform_->scale_)), mask);
	}

	SetDrawer(GateDrawer::Create(nullptr, nullptr, 2));
}

void Gate::UpdateBeforeCollision()
{
	GameObject::UpdateBeforeCollision();
}

void Gate::UpdateAfterCollision()
{
	UpdatePos();

	GameObject::UpdateAfterCollision();
}

YGame::InfoOnCollision Gate::GetInfoOnCollision()
{
	InfoOnCollision result;

	result.attribute = AttributeType::eGate;
	result.pTrfm = transform_.get();
	result.radius = 0.0f;
	result.pStatus = nullptr;

	return result;
}

void Gate::OnCollision(const InfoOnCollision& info)
{
	if (drawer_->IsActAnimation(static_cast<uint32_t>(GateDrawer::AnimationType::ePass))) { return; }

	if (info.attribute == AttributeType::ePlayer)
	{
		drawer_->PlayAnimation(static_cast<uint32_t>(GateDrawer::AnimationType::ePass));
	}
}
