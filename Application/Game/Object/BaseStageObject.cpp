#include "BaseStageObject.h"

#include "WorldManager.h"

#include "MathVector.h"

using YGame::BaseStageObject;
using YGame::WorldManager;
using YMath::Vector3;

namespace
{
	WorldManager* pWorldMan = WorldManager::GetInstance();
}

void BaseStageObject::Initialize(
	const std::string& name, 
	const std::string& worldKey, 
	const Transform::Status& status, 
	YMath::Matrix4* pParent)
{
	GameObject::Initialize(name, status);

	transform_->parent_ = pParent;
	transform_->UpdateMatrix();

	SetWorldKey(worldKey);
}

void BaseStageObject::SetWorldKey(const std::string& worldKey)
{
	worldKey_ = worldKey;

	SetUpdateKey(worldKey);
	SetDrawKeys({ worldKey });

	if (drawer_) { drawer_->SetVPkey(worldKey); }
}

void BaseStageObject::UpdatePos()
{
	worldPos_ = initPos_ + localPos_;

	transform_->pos_ = worldPos_;

	posMat_ = YMath::MatTranslation(transform_->pos_) * pWorldMan->BasePosMat();
}

Vector3 BaseStageObject::WorldPos() const
{
	return worldPos_;
}
