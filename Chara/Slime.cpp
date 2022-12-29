#include "Slime.h"
#include "CharaConfig.h"
#include "CollisionConfig.h"
#include "CalcTransform.h"
#include "YMath.h"
#include <cassert>

#pragma region –¼‘O‹óŠÔ
using CharaConfig::GravityPower;
using CharaConfig::Enemy::CheatTime;
using namespace CharaConfig::Enemy::Slime;
#pragma endregion

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
	InitializeCharacter(
		{
			state.pos_,
			YMath::AdjustAngle(YMath::Vec3(0, 0, -1)),
			{5.0f,5.0f,5.0f}
		}
	);
	InitializeCharaStatus({ HP, CheatTime });
	InitializeMapCollisionStatus({ obj_.scale_ });
	InitializeSlimeAct();
}

void Slime::Update()
{
	UpdateGravity();

	obj_.pos_ += speed_;

	UpdateCharaStatus();
	obj_.color_.g_ = (1.0f - isCheat() * 1.0f);
	obj_.color_.b_ = (1.0f - isCheat() * 1.0f);
	obj_.color_.a_ = (1.0f - isCheat() * 0.5f);

	UpdateSlimeAct();

	obj_.UniqueUpdate({ {}, {}, SlimeActValue() });
}

void Slime::Draw(const YGame::ViewProjection& vp)
{
	pModel_->Draw(obj_, vp, tex_);
}
