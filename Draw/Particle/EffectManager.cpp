#include "EffectManager.h"

using YGame::EffectManager;

void EffectManager::StaticInitialize(ParticleManager* pParticleMan)
{
	// ���N���X
	IEffect::StaticInitialize(pParticleMan);
}

void EffectManager::Initialize()
{
	// �G�t�F�N�g�S�폜
	if (effects_.empty() == false)
	{
		effects_.clear();
	}
}

void EffectManager::Update()
{
	// �G�t�F�N�g���񂾂�폜
	effects_.remove_if([](std::unique_ptr<IEffect>& particle) { return particle->isAlive_ == false; });

	// �G�t�F�N�g���X�V
	for (std::unique_ptr<IEffect>& effect : effects_)
	{
		effect->Update();
	}
}

void EffectManager::Draw()
{
	// �G�t�F�N�g�`��
	for (std::unique_ptr<IEffect>& effect : effects_)
	{
		effect->Draw();
	}
}
