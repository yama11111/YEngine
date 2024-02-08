#include "ViewProjectionManager.h"
#include <cassert>

using YGame::ViewProjection;
using YGame::ViewProjectionManager;

ViewProjectionManager* ViewProjectionManager::GetInstance()
{
	static ViewProjectionManager instance;
	return &instance;
}

void ViewProjectionManager::Clear()
{
	pVPs_.clear();
}

void ViewProjectionManager::Erase(const std::string& key)
{
	assert(pVPs_.contains(key));
	pVPs_.erase(key);
}

void ViewProjectionManager::Insert(const std::string& key, ViewProjection* pVP)
{
	assert(pVP);
	if (pVPs_.contains(key)) { pVPs_[key] = pVP; }
	pVPs_.insert({ key, pVP });
}

ViewProjection* ViewProjectionManager::ViewProjectionPtr(const std::string& key)
{
	assert(pVPs_.contains(key));
	return pVPs_[key];
}
