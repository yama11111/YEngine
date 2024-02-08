#include "BaseStageObject.h"
#include "WorldManager.h"

using YGame::BaseStageObject;
using YGame::WorldManager;
using YMath::Vector3;

namespace
{
	WorldManager* pWorldMan = WorldManager::GetInstance();
}

void BaseStageObject::UpdatePos()
{
	worldPos_ = initPos_ + localPos_;

	transform_->pos_ = worldPos_;
}

Vector3 BaseStageObject::WorldPos() const
{
	return worldPos_;
}
