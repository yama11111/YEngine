#include "Outside.h"
#include "OutsideDrawer.h"
#include "WorldManager.h"

using YGame::Outside;
using YMath::BitFrag;

namespace
{
}

std::unique_ptr<Outside> Outside::Create(const Transform::Status& status, WorldKey key)
{
	std::unique_ptr<Outside> newObj = std::make_unique<Outside>();

	newObj->Initialize(status, key);

	return std::move(newObj);
}

void Outside::Initialize(const Transform::Status& status, WorldKey key)
{
	BaseStageObject::Initialize("Outside", key, status);

	// 描画
	{
		std::unique_ptr<OutsideDrawer> drawer = OutsideDrawer::Create({ nullptr, nullptr, "Game", 2 });
		drawer->SetParentPosMatPointer(&posMat_);
		drawer->SetWorldKey(worldKey_);
		SetDrawer(std::move(drawer));
	}
}

void Outside::UpdateBeforeCollision()
{
	GameObject::UpdateBeforeCollision();
}

void Outside::UpdateAfterCollision()
{
	GameObject::UpdateAfterCollision();
}