#include "Particle.h"
#include <cassert>

using YGame::IParticle;
using YGame::ModelObject;
using YGame::ViewProjection;
using YGame::Model;
using YGame::Color;
using YMath::Vector3;
using YMath::Vector4;

ViewProjection* IParticle::spVP_ = nullptr;

void IParticle::StaticInitialize(YGame::ViewProjection* pVP)
{
	// nullチェック
	assert(pVP);
	// 代入
	spVP_ = pVP;
}
