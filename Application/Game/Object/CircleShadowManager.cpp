#include "CircleShadowManager.h"
#include <cassert>
#include <imgui.h>

using YGame::CircleShadowManager;
using YGame::BaseConstBuffer;

namespace 
{
	const YMath::Vector3 kDirection = { 0.0f,-1.0f,0.0f };
	const float kDistance = 100.0f;
	const YMath::Vector3 kAtten = { 0.5f,0.6f,0.0f };
	const float kStartFactor = 0.005f;
	const float kEndFactor = 0.01f;
}

void CircleShadowManager::Intialize()
{
	for (size_t i = 0; i < cbShadow_.size(); i++)
	{
		if (cbShadow_[i] == nullptr)
		{
			cbShadow_[i].reset(ConstBufferObject<CBShadowGroup>::Create());
		}
	}

	Reset();
}

void CircleShadowManager::Reset()
{

	for (size_t i = 0; i < cbShadow_.size(); i++)
	{
		for (size_t j = 0; j < cbShadow_[i]->data_.circleShadows_.size(); j++)
		{
			cbShadow_[i]->data_.circleShadows_[j].shadowDir = kDirection;
			cbShadow_[i]->data_.circleShadows_[j].casterPos = {};
			cbShadow_[i]->data_.circleShadows_[j].distanceFromCasterToShadow = kDistance;
			cbShadow_[i]->data_.circleShadows_[j].shadowAtten = kAtten;
			cbShadow_[i]->data_.circleShadows_[j].shadowStartFactorAngleCos = kStartFactor;
			cbShadow_[i]->data_.circleShadows_[j].shadowEndFactorAngleCos = kEndFactor;
			cbShadow_[i]->data_.circleShadows_[j].active = 0.0f;
		}
	}
}

void CircleShadowManager::ActivateCircleShadow(const size_t index, const YMath::Vector3& pos)
{
	assert(0 <= index && index < cbShadow_.size());
	assert(cbShadow_[index]);

	for (size_t i = 0; i < cbShadow_[index]->data_.circleShadows_.size(); i++)
	{
		// 既に使われているなら弾く
		if (1.0f <= cbShadow_[index]->data_.circleShadows_[i].active) { continue; }
		
		cbShadow_[index]->data_.circleShadows_[i].casterPos = pos;
		cbShadow_[index]->data_.circleShadows_[i].active = 1.0f;

		return;
	}
}

BaseConstBuffer* CircleShadowManager::CBPtr(const size_t index)
{
	assert(0 <= index && index < cbShadow_.size());
	assert(cbShadow_[index]);
	return cbShadow_[index].get();
}

CircleShadowManager* CircleShadowManager::GetInstance()
{
	static CircleShadowManager instance;
	return &instance;
}
