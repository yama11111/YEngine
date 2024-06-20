#include "BaseGameParticle.h"
#include "WorldManager.h"

using YGame::BaseGameParticle;

void BaseGameParticle::Initialize(
	const WorldKey worldKey, 
	const uint32_t aliveFrame, 
	const Transform::Status& status, 
	const std::string& shaderTag, 
	const uint16_t drawPriority)
{
	BaseParticle::Initialize(aliveFrame, status, shaderTag, drawPriority);

	SetWorldKey(worldKey);
}

void BaseGameParticle::SetWorldKey(const WorldKey worldKey)
{
	worldKey_ = worldKey;
	
	obj_->transform_.parent_ = WorldManager::GetInstance()->BasePosMatPointer(worldKey);
}
