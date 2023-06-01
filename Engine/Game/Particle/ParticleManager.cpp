#include "ParticleManager.h"
#include "MathUtillity.h"
#include "YAssert.h"
#include "Def.h"

using std::unique_ptr;
using YGame::ParticleManager;
using YGame::Transform;
using YGame::Model;
using YGame::Sprite3D;
using YMath::Ease;
using YMath::Vector3;
using YMath::Vector4;
using YMath::GetRand;

Model* ParticleManager::spGridModel_ = nullptr;
Sprite3D* ParticleManager::spCharacterSprite3D_ = nullptr;

void ParticleManager::StaticInitialize(YGame::ViewProjection* pVP)
{
	// ���N���X
	IParticleModel::StaticInitialize(pVP);

	IParticleSprite3D::StaticInitialize(pVP);
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
