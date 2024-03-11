#include "CircleShadowManager.h"
#include <cassert>
#include <imgui.h>

using YGame::CircleShadowManager;
using YGame::BaseConstBuffer;

namespace 
{
	const std::array<CircleShadowManager::Key, 
		static_cast<size_t>(CircleShadowManager::Key::eKeyNum)> kKeys =
	{
		CircleShadowManager::Key::eWorld_0,
		CircleShadowManager::Key::eWorld_1,
		CircleShadowManager::Key::eWorld_2,
	};

	const YMath::Vector3 kDirection = { 0.0f,-1.0f,0.0f };
	const float kDistance = 100.0f;
	const YMath::Vector3 kAtten = { 0.5f,0.6f,0.0f };
	const float kStartFactor = 0.005f;
	const float kEndFactor = 0.01f;
}

void CircleShadowManager::Intialize()
{
	cbShadow_.clear();
	for (size_t i = 0; i < kKeys.size(); i++)
	{
		cbShadow_.insert({ kKeys[i], std::unique_ptr<ConstBufferObject<CBShadowGroup>>()});
	}
	
	for (auto itr = cbShadow_.begin(); itr != cbShadow_.end(); ++itr)
	{
		if (itr->second == nullptr)
		{
			itr->second.reset(ConstBufferObject<CBShadowGroup>::Create());
		}
	}

	Reset();
}

void CircleShadowManager::Reset()
{
	for (auto itr = cbShadow_.begin(); itr != cbShadow_.end(); ++itr)
	{
		for (size_t i = 0; i < itr->second->data_.circleShadows_.size(); i++)
		{
			itr->second->data_.circleShadows_[i].shadowDir = kDirection;
			itr->second->data_.circleShadows_[i].casterPos = {};
			itr->second->data_.circleShadows_[i].distanceFromCasterToShadow = kDistance;
			itr->second->data_.circleShadows_[i].shadowAtten = kAtten;
			itr->second->data_.circleShadows_[i].shadowStartFactorAngleCos = kStartFactor;
			itr->second->data_.circleShadows_[i].shadowEndFactorAngleCos = kEndFactor;
			itr->second->data_.circleShadows_[i].active = 0.0f;
		}
	}
}

void CircleShadowManager::ActivateCircleShadow(const Key key, const YMath::Vector3& pos)
{
	assert(cbShadow_[key]);
	
	for (size_t i = 0; i < cbShadow_[key]->data_.circleShadows_.size(); i++)
	{
		// 既に使われているなら弾く
		if (1.0f <= cbShadow_[key]->data_.circleShadows_[i].active) { continue; }

		cbShadow_[key]->data_.circleShadows_[i].casterPos = pos;
		cbShadow_[key]->data_.circleShadows_[i].active = 1.0f;

		return;
	}
}

BaseConstBuffer* CircleShadowManager::CBPtr(const Key key)
{
	assert(cbShadow_[key]);
	
	return cbShadow_[key].get();
}

CircleShadowManager* CircleShadowManager::GetInstance()
{
	static CircleShadowManager instance;
	return &instance;
}
