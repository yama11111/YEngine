#include "ParticleManager.h"
#include "MathUtillity.h"
#include "YAssert.h"

using YGame::ParticleManager;
using YGame::Model;
using YMath::Vector3;

const float PI = 3.141592f;

Model* ParticleManager::pModel_ = nullptr;

void ParticleManager::StaticInitialize(YGame::Model* pModel)
{
	pModel_ = pModel;
}

void ParticleManager::Initialize()
{
	// パーティクル全削除
	if (particles_.empty() == false)
	{
		particles_.clear();
	}
}

void ParticleManager::Update()
{
	// パーティクル死んだら削除
	particles_.remove_if([](std::unique_ptr<IParticle>& particle) { return particle->isAlive_ == false; });

	// パーティクル毎更新
	for (std::unique_ptr<IParticle>& particle : particles_)
	{
		particle->Update();
	}
}

void ParticleManager::Draw(const YGame::ViewProjection& vp, YGame::LightGroup* pLightGroup)
{
	// パーティクル描画
	for (std::unique_ptr<IParticle>& particle : particles_)
	{
		particle->Draw(vp, pLightGroup);
	}
}

void ParticleManager::EmitFireSpark(
	const YMath::Vector3& pos,
	const YMath::Vector3& range,
	const float maxScale,
	const YMath::Vector3& speed,
	const YMath::Vector4& color,
	const uint32_t frame, const size_t num)
{
	for (size_t i = 0; i < num; i++)
	{
		std::unique_ptr<FireSpark> newParticle = std::make_unique<FireSpark>();

		uint32_t swayT = frame / YMath::GetRand(1, 2);

		Vector3 p = pos;
		p.x_ += YMath::GetRand(-range.x_, range.x_, 100.0f);
		p.y_ += YMath::GetRand(-range.y_, range.y_, 100.0f);
		p.z_ += YMath::GetRand(-range.z_, range.z_, 100.0f);
		float s = YMath::GetRand(maxScale / 2.0f, maxScale, 100.0f);

		newParticle->Emit(frame, swayT, speed, p, s, color);
		particles_.push_back(std::move(newParticle));
	}
}