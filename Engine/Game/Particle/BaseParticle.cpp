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

	if (obj_) 
	{
		obj_->Initialize(status); 
	}

	initPos_ = status.pos_;

	localPos_ = {};

	worldPos_ = initPos_;

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

		if (obj_) 
		{
			obj_->SetIsVisible(false); 
		}
	}
}

void BaseParticle::Draw()
{
	if (isAlive_ == false) { return; }

	if (obj_)
	{
		obj_->Draw(shaderTag_, drawPriority_);
	}
}

void BaseParticle::SetObject(BaseDrawObject* obj)
{
	assert(obj);

	obj_.reset(obj);
}
