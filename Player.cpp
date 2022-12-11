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
	Reset();
}

void Player::Reset()
{
	obj_.Initialize({ {0.0f, 50.0f, 50.0f}, {}, {5.0f,5.0f,5.0f} });
	obj_.rota_ = Math::AdjustAngle(Math::Vec3(0, 0, 1));
	speed_ = { 0.0f,0.0f,0.0f };

	InitializeCollisionStatus(
		{
			CollRad,
			Collision::Attribute::Player,
			Collision::Attribute::Enemy
		}
	);

	InitializeMapCollisionStatus({obj_.scale_});

	jumpCount_ = 0;
}

void Player::OnCollision(const uint32_t attribute)
{

}

void Player::Jump()
{
	if (++jumpCount_ > MaxJumpCount) { /*return;*/ }

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
}

void Player::UpdateMove() 
{
	obj_.pos_ += speed_;
}

void Player::UpdateMatrix() 
{
	obj_.Update();
}

void Player::Draw(const Game::ViewProjection& vp)
{
	pModel_->Draw(obj_, vp, tex_);
}

