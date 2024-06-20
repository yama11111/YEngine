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

std::unique_ptr<Gate> Gate::Create(const Transform::Status& status, const WorldKey key)
{
	std::unique_ptr<Gate> newObj = std::make_unique<Gate>();

	newObj->Initialize(status, key);

	return std::move(newObj);
}

void Gate::Initialize(const Transform::Status& status, const WorldKey key)
{
	BaseStageObject::Initialize("Gate", key, status);

	// アタリ判定
	{
		BitFrag attribute{};
		attribute.SetFragTrue(AttributeType::eGate);

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
		std::unique_ptr<GateDrawer> drawer = GateDrawer::Create({ nullptr, nullptr, "Game", 2 });
		drawer->SetParentPosMatPointer(&posMat_);
		drawer->SetWorldKey(worldKey_);
		if (status.scale_.IsZero()) { drawer->SetIsVisible(false); }
		SetDrawer(std::move(drawer));
	}
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

YGame::ICollisionInfomation Gate::GetCollisionInfomation()
{
	ICollisionInfomation result = BaseStageObject::GetCollisionInfomation();

	result.attribute = AttributeType::eGate;
	result.radius = 0.0f;

	return result;
}

void Gate::OnCollision(const ICollisionInfomation& info)
{
	if (worldKey_ == WorldKey::eJourneyKey)
	{
		return;
	}
	if (drawer_->IsActAnimation(static_cast<uint32_t>(GateDrawer::AnimationType::eShrink))) 
	{
		return; 
	}

	if (info.attribute == AttributeType::ePlayer)
	{
		drawer_->PlayAnimation(static_cast<uint32_t>(GateDrawer::AnimationType::eShrink));
	}
}
