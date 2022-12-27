#include "Player.h"
#include "CharaConfig.h"
#include "CollisionConfig.h"
#include "CalcTransform.h"
#include "MapChipManager.h"
#include "YMath.h"
#include <cassert>

#pragma region –¼‘O‹óŠÔ
using CharaConfig::GravityPower;
using CharaConfig::Player::CollRad;
using CharaConfig::Player::HP;
using CharaConfig::Player::MaxJumpCount;
using CharaConfig::Player::RisePower;
#pragma endregion

YGame::Model* Player::pModel_ = nullptr;
UINT Player::tex_ = UINT_MAX;

void Player::StaticIntialize(const StaticInitStatus& state)
{
	assert(state.pModel_);
	pModel_ = state.pModel_;
	tex_ = state.tex_;
}

void Player::Initialize(const InitStatus& state)
{
	InitializeCollisionStatus(
		{
			CollRad,
			Collision::Attribute::Player,
			Collision::Attribute::Enemy
		}
	);
	Reset(state);
}

void Player::Reset(const InitStatus& state)
{
	obj_.Initialize({ state.pos_, {}, {5.0f,5.0f,5.0f} });
	obj_.rota_ = YMath::AdjustAngle(YMath::Vec3(0, 0, 1));
	speed_ = { 0.0f,0.0f,0.0f };

	InitializeMapCollisionStatus({obj_.scale_});
	InitializeCharaStatus({ HP });

	jumpCount_ = 0;
}

void Player::OnCollision(const uint32_t attribute)
{
	obj_.pos_.z_ = 10;
}

void Player::Jump()
{
	if (++jumpCount_ > MaxJumpCount) { return; }

	jumpCount_ = min(jumpCount_, MaxJumpCount);
	speed_.y_ = RisePower;
}
void Player::UpdateJump()
{
	speed_.y_ -= GravityPower;

	if (IsLanding()) 
	{
		jumpCount_ = 0;
	}
}

void Player::Attack()
{

}
void Player::UpdateAttack()
{

}

void Player::Update()
{
	UpdateJump();
	UpdateAttack();

	pMapChip_->Collision(*this);

	obj_.pos_ += speed_;
	obj_.Update();
}

void Player::Draw(const YGame::ViewProjection& vp)
{
	pModel_->Draw(obj_, vp, tex_);
}

