#include "MeteorEmitter.h"
#include "MeteorParticle.h"
#include "ViewProjectionManager.h"
#include "ColorConfig.h"
#include "Def.h"


#include "WorldManager.h"

#include <cmath>

using YGame::MeteorEmitter;
using YGame::ViewProjectionManager;
using YMath::Vector3;
using YMath::Vector4;
using YMath::BitFrag;

namespace
{
	const Vector4 kColor = YGame::ColorConfig::skTurquoise[0];

	ViewProjectionManager* pVPMan = ViewProjectionManager::GetInstance();
}

std::unique_ptr<MeteorEmitter> MeteorEmitter::Create(const Transform::Status& status, const std::string& key)
{
	std::unique_ptr<MeteorEmitter> newObj = std::make_unique<MeteorEmitter>();

	newObj->Initialize(status, key);

	return std::move(newObj);
}

void MeteorEmitter::Initialize(const Transform::Status& status, const std::string& key)
{
	GameObject::Initialize("Skydome", status);

	SetUpdateKey(key);

	isEmit_ = false;
	emitCount_ = 0;
}

void MeteorEmitter::UpdateBeforeCollision()
{
	GameObject::UpdateBeforeCollision();
}

void MeteorEmitter::UpdateAfterCollision()
{
	GameObject::UpdateAfterCollision();

	isEmit_ = WorldManager::GetInstance()->CurrentWorldKey() == WorldKey::eJourneyKey;

	if (isEmit_)
	{
		float angle = (kPI * 2.0f) / 36 * emitCount_;
		Vector3 angleVec = Vector3(0.0f, cosf(angle), sinf(angle));

		MeteorParticle::Emit(
			transform_->pos_ + Vector3(30.0f * angleVec),
			Vector3(-20.0f, 0.0f, 0.0f), 
			kColor, 
			pVPMan->ViewProjectionPtr(updateKey_));

		emitCount_++;
		if (36 < emitCount_) { emitCount_ = 0; }
	}
}