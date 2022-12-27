#include "Slime.h"
#include "CharaConfig.h"
#include "CollisionConfig.h"
#include "CalcTransform.h"
#include "MapChipManager.h"
#include "YMath.h"
#include <cassert>

#pragma region –¼‘O‹óŠÔ
using CharaConfig::GravityPower;
using CharaConfig::Enemy::Slime::CollRad;
using CharaConfig::Enemy::Slime::HP;
#pragma endregion

const float CollRad = 10.0f;
const float GravityPower = 0.3f;

YGame::Model* Slime::pModel_ = nullptr;
UINT Slime::tex_ = UINT_MAX;

void Slime::StaticIntialize(const StaticInitStatus& state)
{
	assert(state.pModel_);
	pModel_ = state.pModel_;
	tex_ = state.tex_;
}

void Slime::Initialize(const InitStatus& state)
{
	InitializeCollisionStatus(
		{
			CollRad,
			Collision::Attribute::Enemy,
			Collision::Attribute::Player
		}
	);
	Reset(state);
}

void Slime::Reset(const InitStatus& state)
{
	obj_.Initialize({ state.pos_, {}, {5.0f,5.0f,5.0f} });
	obj_.rota_ = YMath::AdjustAngle(YMath::Vec3(0, 0, -1));
	speed_ = { 0.0f,0.0f,0.0f };

	InitializeMapCollisionStatus({ obj_.scale_ });
	InitializeCharaStatus({ HP });
}

void Slime::Update()
{
	speed_.y_ -= GravityPower;

	pMapChip_->Collision(*this);

	obj_.pos_ += speed_;
	obj_.Update();
}

void Slime::Draw(const YGame::ViewProjection& vp)
{
	pModel_->Draw(obj_, vp, tex_);
}
