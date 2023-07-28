#include "BaseParticle.h"
#include <cassert>

using YGame::BaseParticle;

void BaseParticle::Initialize(
	const uint32_t aliveFrame, 
	BaseDrawObject* obj, 
	const std::string& shaderTag, 
	const uint16_t drawPriority)
{
	assert(obj);

	isAlive_ = true;

	aliveTimer_.Initialize(aliveFrame, true);

	obj_.reset(obj);

	shaderTag_ = shaderTag;

	drawPriority_ = drawPriority;
}

void BaseParticle::Update()
{
	UpdateLife();

	obj_->Update();
}

void BaseParticle::Draw()
{
	obj_->Draw(shaderTag_, drawPriority_);
}

void BaseParticle::UpdateLife()
{
	if (isAlive_ == false) { return; }

	aliveTimer_.Update();
	
	// 生存タイマー終了時死亡
	if (aliveTimer_.IsEnd()) 
	{
		isAlive_ = false; 
	}
}
