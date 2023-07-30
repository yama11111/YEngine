#include "BaseParticle.h"
#include <cassert>

using YGame::BaseParticle;

void BaseParticle::Initialize(
	const uint32_t aliveFrame, 
	const Transform::Status& status, 
	const std::string& shaderTag, 
	const uint16_t drawPriority)
{
	isAlive_ = true;

	aliveTimer_.Initialize(aliveFrame, true);

	obj_->Initialize(status);

	shaderTag_ = shaderTag;

	drawPriority_ = drawPriority;
}

void BaseParticle::UpdateLife()
{
	if (isAlive_ == false) { return; }

	aliveTimer_.Update();
	
	// 生存タイマー終了時死亡
	if (aliveTimer_.IsEnd()) 
	{
		isAlive_ = false; 

		obj_->SetVisible(false);
	}
}

void BaseParticle::Draw()
{
	if (isAlive_ == false) { return; }

	obj_->Draw(shaderTag_, drawPriority_);
}

void BaseParticle::SetObject(BaseDrawObject* obj)
{
	assert(obj);

	obj_.reset(obj);
}
