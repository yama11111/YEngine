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
	// �p�[�e�B�N���S�폜
	if (particles_.empty() == false)
	{
		particles_.clear();
	}
}

void ParticleManager::PushBack(BaseParticle* newParticle)
{
	assert(newParticle);

	std::unique_ptr<BaseParticle> uniquePtcl;

	uniquePtcl.reset(newParticle);

	particles_.push_back(std::move(uniquePtcl));
}

void ParticleManager::Update()
{
	// �p�[�e�B�N�������񂾂�폜
	particles_.remove_if([](std::unique_ptr<BaseParticle>& particle) { return particle->IsAlive() == false; });

	for (std::unique_ptr<BaseParticle>& particle : particles_)
	{
		particle->Update();
	}
}

void ParticleManager::Draw()
{
	for (std::unique_ptr<BaseParticle>& particle : particles_)
	{
		particle->Draw();
	}
}
