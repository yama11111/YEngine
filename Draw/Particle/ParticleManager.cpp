#include "ParticleManager.h"
#include "MathUtillity.h"
#include "YAssert.h"

using YParticle::ParticleManager;
using YGame::Model;
using YMath::Vec3;

Model* ParticleManager::pModel_ = nullptr;

const float PI = 3.141592f;

void ParticleManager::StaticInitialize(const StaticInitStatus& state)
{
	assert(state.pModel_);

	pModel_ = state.pModel_;
}

void ParticleManager::Initialize()
{
	if (particles_.empty() == false)
	{
		particles_.clear();
	}
}

void ParticleManager::Update()
{
	particles_.remove_if([](std::unique_ptr<IParticle>& particle) { return particle->isAlive_ == false; });
	for (std::unique_ptr<IParticle>& particle : particles_)
	{
		particle->Update();
	}
}

void ParticleManager::Draw(const YGame::ViewProjection& vp)
{
	for (std::unique_ptr<IParticle>& particle : particles_)
	{
		//pModel_->Draw(particle->obj_, vp);
	}
}

void ParticleManager::EmitDust(YMath::Vec3& pos, YMath::Vec3& direction, uint32_t frame, size_t num)
{
	//for (size_t i = 0; i < num; i++)
	//{
	//	std::unique_ptr<Dust> newParticle = std::make_unique<Dust>();
	//	Vec3 r = Vec3(
	//		{
	//			YMath::GetRand(0.0f, PI * 2.0f * 100.0f) / 100.0f,
	//			YMath::GetRand(0.0f, PI * 2.0f * 100.0f) / 100.0f,
	//			YMath::GetRand(0.0f, PI * 2.0f * 100.0f) / 100.0f
	//		}
	//	);

	//	float s = YMath::GetRand(200, 400) / 1000.0f;

	//	newParticle->Emit({ pos, r, s, direction * 0.5f, frame });
	//	particles_.push_back(std::move(newParticle));
	//}
}

void ParticleManager::EmitExprosion(YMath::Vec3& pos, float speed, YMath::Vec4 color, uint32_t frame, size_t num)
{
	//for (size_t i = 0; i < num; i++)
	//{
	//	std::unique_ptr<Exprosion> newParticle = std::make_unique<Exprosion>();
	//	Vec3 spd = Vec3(
	//		{
	//			YMath::GetRand(10.0f, 20.0f) / 100.0f * speed,
	//			YMath::GetRand(10.0f, 20.0f) / 100.0f * speed,
	//			YMath::GetRand(10.0f, 20.0f) / 100.0f * speed
	//		}
	//	);

	//	float s = YMath::GetRand(200, 400) / 1000.0f;

	//	newParticle->Emit({ pos, s, spd, color, frame });
	//	particles_.push_back(std::move(newParticle));
	//}
}

void ParticleManager::EmitEruption(YMath::Vec3& pos, YMath::Vec3& direction, uint32_t frame, size_t num)
{
	
}
