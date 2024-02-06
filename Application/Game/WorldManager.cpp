#include "WorldManager.h"
#include <cassert>

using YGame::WorldManager;
using YMath::Vector3;

namespace
{
	const std::array<std::string, static_cast<size_t>(WorldManager::Key::eNum)> kKeyStrs = 
	{
		"Start", "World", "Fever", "Goal",
	};
}

WorldManager* WorldManager::GetInstance()
{
	static WorldManager instance;
	return &instance;
}

void WorldManager::Initialize(const Key& key)
{
	SetWorldKey(key);
	
	for (size_t i = 0; i < mileages_.size(); i++)
	{
		mileages_[i] = {};
	}
}

void WorldManager::ResetMileage(const Key& key)
{
	size_t index = static_cast<size_t>(key);
	assert(0 <= index || index < kKeyNum);

	mileages_[index] = {};
}

void WorldManager::SetWorldKey(const Key& key)
{
	currentWorldKey_ = key;
}

void WorldManager::SetMileage(const Key& key, const Vector3 mileage)
{
	size_t index = static_cast<size_t>(key);
	assert(0 <= index || index < kKeyNum);

	mileages_[index] = mileage;
}

std::string WorldManager::WorldKeyStr(const Key& key) const
{
	size_t index = static_cast<size_t>(key);
	assert(0 <= index || index < kKeyNum);

	return kKeyStrs[static_cast<size_t>(currentWorldKey_)];
}

WorldManager::Key WorldManager::CurrentWorldKey() const
{
	return currentWorldKey_;
}

std::string WorldManager::CurrentWorldKeyStr() const
{
	return kKeyStrs[static_cast<size_t>(currentWorldKey_)];
}

Vector3 WorldManager::Mileage(const Key& key) const
{
	size_t index = static_cast<size_t>(key);
	assert(0 <= index  || index < kKeyNum);

	return mileages_[index];
}

Vector3 WorldManager::CurrentMileage() const
{
	return mileages_[static_cast<size_t>(currentWorldKey_)];
}

