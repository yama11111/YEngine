#include "Effect.h"
#include <cassert>

using YGame::IEffect;
using YGame::ParticleManager;

ParticleManager* IEffect::spParticleMan_ = nullptr;

void IEffect::StaticInitialize(ParticleManager* pParticleMan)
{
	// nullチェック
	assert(pParticleMan);
	// 代入
	spParticleMan_ = pParticleMan;
}
