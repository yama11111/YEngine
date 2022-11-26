#include "Player.h"
#include "CollisionConfig.h"
#include "CalcTransform.h"
#include "YMath.h"
#include <cassert>

const float CollRad = 1.0f;

Game::Model* Player::model_ = nullptr;
UINT Player::tex_ = UINT_MAX;


void Player::StaticIntialize(const StaticInitStatus& state)
{
	assert(state.model_);
	model_ = state.model_;
	tex_ = state.tex_;
}

void Player::Initialize()
{
	keys_ = Input::Keys::GetInstance();
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
	obj_.Initialize({});
	obj_.rota_ = Math::AdjustAngle(Math::Vec3(0, 0, 1));
	SetIsSlip(false);
}

void Player::OnCollision(const uint32_t attribute)
{

}

void Player::Jump()
{

}

void Player::Update()
{
	Jump();
	obj_.Update();
}

void Player::Draw(const Game::ViewProjection& vp)
{
	model_->Draw(obj_, vp, tex_);
}

