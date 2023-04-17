#include "Effect.h"
#include <cassert>

using YGame::IEffect;
using YGame::ParticleManager;

ParticleManager* IEffect::spParticleMan_ = nullptr;

void IEffect::StaticInitialize(ParticleManager* pParticleMan)
{
	// null�`�F�b�N
	assert(pParticleMan);
	// ���
	spParticleMan_ = pParticleMan;
}
