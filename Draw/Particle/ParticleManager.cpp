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
	
	// �ԉ�
	FireWork::StaticInitialize(Model::CreateCube());
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

void YGame::ParticleManager::EmitFireWorks(
	const uint32_t frame, const size_t num, 
	const YMath::Vector3& pos, const float scale, 
	const YMath::Vector4& color)
{
	for (size_t i = 0; i < num; i++)
	{
		// �p�[�e�B�N��
		std::unique_ptr<FireWork> newParticle = std::make_unique<FireWork>();

		// ----- �ʒu ----- //
		Ease<Vector3> posEas;

		// �I�_
		Vector3 posEnd = pos;
		// �͈�
		float posRange = scale * 3.0f;
		
		// �ݒ�
		posEnd.x_ += YMath::GetRand(-posRange, posRange, 100.0f);
		posEnd.y_ += YMath::GetRand(-posRange, posRange, 100.0f);
		posEnd.z_ += YMath::GetRand(-posRange, posRange, 100.0f);

		// ������
		posEas.Initialize(pos, posEnd, 3.0f);


		// ----- ��] ----- //
		Ease<Vector3> rotaEas;
		
		// �I�_
		Vector3 rotaEnd = {};
		// �͈�
		float rotaRange = PI * 2.0f;

		// �ݒ�
		rotaEnd.x_ += YMath::GetRand(-rotaRange, rotaRange, 100.0f);
		rotaEnd.y_ += YMath::GetRand(-rotaRange, rotaRange, 100.0f);
		rotaEnd.z_ += YMath::GetRand(-rotaRange, rotaRange, 100.0f);

		// ������
		rotaEas.Initialize({}, rotaEnd, 3.0f);


		// ����
		newParticle->Emit(frame, posEas, rotaEas, scale / 3.0f, color);
		// �}��
		particles_.push_back(std::move(newParticle));
	}
}