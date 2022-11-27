#include "Player.h"
#include "CollisionConfig.h"
#include "CalcTransform.h"
#include "YMath.h"
#include <cassert>

const float CollRad = 1.0f;

const int MaxJumpCount = 2;
const int MaxJumpCountAdrenaline = 3;

const float RisePower = 4.5f;
const float GravityPower = 0.3f;
const float Ground = 5.0f;

Game::Model* Player::pModel_ = nullptr;
UINT Player::tex_ = UINT_MAX;

void Player::StaticIntialize(const StaticInitStatus& state)
{
	assert(state.pModel_);
	pModel_ = state.pModel_;
	tex_ = state.tex_;
}

void Player::Initialize()
{
	InitializeCollisionStatus(
		{
			CollRad,
			Collision::Attribute::Player,
			Collision::Attribute::Enemy
		}
	);
	Reset();
}

void Player::Reset()
{
	obj_.Initialize({ {0.0f, Ground, 0.0f}, {}, {5.0f,5.0f,5.0f} });
	obj_.rota_ = Math::AdjustAngle(Math::Vec3(0, 0, 1));
	SetIsSlip(false);
	jumpCount_ = 0;
	jumpPower_ = 0.0f;
	isLanding_ = false;
}

void Player::OnCollision(const uint32_t attribute)
{

}

void Player::Jump()
{
	if (++jumpCount_ > MaxJumpCount) 
	{
		jumpCount_ = MaxJumpCount;
		return; 
	}

	jumpCount_ = min(jumpCount_, MaxJumpCount);
	jumpPower_ = RisePower;
}

void Player::UpdateJump()
{
	obj_.pos_.y_ += jumpPower_;

	jumpPower_ -= GravityPower;

	isLanding_ = (obj_.pos_.y_ <= Ground);
	if (isLanding_) 
	{
		jumpCount_ = 0;
		jumpPower_ = 0.0f;
		obj_.pos_.y_ = Ground;
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
	obj_.Update();
}

void Player::Draw(const Game::ViewProjection& vp)
{
	pModel_->Draw(obj_, vp, tex_);
}

