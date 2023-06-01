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
	// 基底クラス
	IParticleModel::StaticInitialize(pVP);

	IParticleSprite3D::StaticInitialize(pVP);
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

void ParticleManager::Draw()
{
	// パーティクル描画
	for (std::unique_ptr<IParticle>& particle : particles_)
	{
		particle->Draw();
	}
}
