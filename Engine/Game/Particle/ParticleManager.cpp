#include "ParticleManager.h"
#include <assert.h>

using YGame::ParticleManager;

ParticleManager* ParticleManager::GetInstance()
{
	static ParticleManager instance;

	return &instance;
}

void ParticleManager::Clear()
{
	// パーティクル全削除
	if (particles_.empty() == false)
	{
		particles_.clear();
	}
}

void ParticleManager::InsertParticles(const std::string& tag, const std::list<BaseParticle*>& particles)
{
	assert(particles_.contains(tag) == false);

	particles_.insert({ tag, particles });
}

void ParticleManager::Update()
{
	for (auto itr = particles_.begin(); itr != particles_.end(); ++itr)
	{
		for (BaseParticle* pParticle : itr->second)
		{
			pParticle->Update();
		}
	}
}

void ParticleManager::Draw()
{
	for (auto itr = particles_.begin(); itr != particles_.end(); ++itr)
	{
		for (BaseParticle* pParticle : itr->second)
		{
			pParticle->Draw();
		}
	}
}
