#include "EffectManager.h"

using YGame::EffectManager;

void EffectManager::StaticInitialize(ParticleManager* pParticleMan)
{
	// 基底クラス
	IEffect::StaticInitialize(pParticleMan);
}

void EffectManager::Initialize()
{
	// エフェクト全削除
	if (effects_.empty() == false)
	{
		effects_.clear();
	}
}

void EffectManager::Update()
{
	// エフェクト死んだら削除
	effects_.remove_if([](std::unique_ptr<IEffect>& particle) { return particle->isAlive_ == false; });

	// エフェクト毎更新
	for (std::unique_ptr<IEffect>& effect : effects_)
	{
		effect->Update();
	}
}

void EffectManager::Draw()
{
	// エフェクト描画
	for (std::unique_ptr<IEffect>& effect : effects_)
	{
		effect->Draw();
	}
}
