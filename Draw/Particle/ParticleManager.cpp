#include "ParticleManager.h"
#include "MathUtillity.h"
#include "YAssert.h"
#include "Def.h"

using YGame::ParticleManager;
using YGame::Model;
using YMath::Ease;
using YMath::Vector3;

void ParticleManager::StaticInitialize(YGame::ViewProjection* pVP)
{
	// ���N���X
	IParticle::StaticInitialize(pVP);

	// ----- ���f���ݒ� ----- //
}

void ParticleManager::Initialize()
{
	// �p�[�e�B�N���S�폜
	if (particles_.empty() == false)
	{
		particles_.clear();
	}
}

void ParticleManager::Update()
{
	// �p�[�e�B�N�����񂾂�폜
	particles_.remove_if([](std::unique_ptr<IParticle>& particle) { return particle->isAlive_ == false; });

	// �p�[�e�B�N�����X�V
	for (std::unique_ptr<IParticle>& particle : particles_)
	{
		particle->Update();
	}
}

void ParticleManager::Draw()
{
	// �p�[�e�B�N���`��
	for (std::unique_ptr<IParticle>& particle : particles_)
	{
		particle->Draw();
	}
}
