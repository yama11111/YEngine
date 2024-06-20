#include "BaseStageObject.h"
#include "BaseStageDrawer.h"

#include "WorldManager.h"

#include "MathVector.h"

#include <cassert>
#include <imgui.h>

using YGame::BaseStageObject;
using YGame::WorldManager;
using YMath::Vector3;

namespace
{
	WorldManager* pWorldMan = WorldManager::GetInstance();
}

void BaseStageObject::Initialize(
	const std::string& name, 
	const WorldKey worldKey,
	const Transform::Status& status)
{
	GameObject::Initialize(name, status);

	SetWorldKey(worldKey);
}

void BaseStageObject::UpdatePos()
{
	worldPos_ = initPos_ + localPos_;

	transform_->pos_ = worldPos_;

	posMat_ = YMath::MatTranslation(transform_->pos_) * pWorldMan->BasePosMat(WorldKeyEnum(updateKey_));
}

void BaseStageObject::SetWorldKey(const WorldKey worldKey)
{
	worldKey_ = worldKey;

	transform_->parent_ = WorldManager::GetInstance()->BasePosMatPointer(worldKey);
	transform_->UpdateMatrix();

	std::string key = WorldKeyStr(worldKey);

	SetUpdateKey(key);
	SetDrawKeys({ key });

	if (drawer_)
	{
		static_cast<BaseStageDrawer*>(drawer_.get())->SetWorldKey(worldKey);
	}
}

Vector3 BaseStageObject::WorldPos() const
{
	return worldPos_;
}

YGame::ICollisionInfomation BaseStageObject::GetCollisionInfomation()
{
	ICollisionInfomation result;

	result.pTrfm = transform_.get();
	result.pWorldPos = &worldPos_;

	return result;
}
