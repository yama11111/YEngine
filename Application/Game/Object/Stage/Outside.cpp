#include "Outside.h"
#include "OutsideDrawer.h"
#include "WorldManager.h"

using YGame::Outside;
using YMath::BitFrag;

namespace
{
}

std::unique_ptr<Outside> Outside::Create(const Transform::Status& status, const std::string& key)
{
	std::unique_ptr<Outside> newObj = std::make_unique<Outside>();

	newObj->Initialize(status, key);

	return std::move(newObj);
}

void Outside::Initialize(const Transform::Status& status, const std::string& key)
{
	BaseStageObject::Initialize("Outside", key, status, WorldManager::GetInstance()->BasePosMatPointer());

	// 描画
	{
		std::unique_ptr<OutsideDrawer> drawer = OutsideDrawer::Create({ nullptr, nullptr, key, 2 });
		drawer->SetParentPosMatPointer(&posMat_);
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