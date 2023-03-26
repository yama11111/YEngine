#include "Player.h"
#include "CharaConfig.h"
#include "CollisionConfig.h"
#include "CalcTransform.h"
#include "YMath.h"
#include <cassert>

#pragma region –¼‘O‹óŠÔ
using YMath::Vector3;
using YGame::ModelObject;
using namespace CharaConfig::Player;
#pragma endregion

YGame::Model* Player::pModel_ = nullptr;
UINT Player::tex_ = UINT_MAX;
YInput::Keys* Player::keys_ = nullptr;

void Player::StaticIntialize(const StaticInitStatus& state)
{
	assert(state.pModel_);

	pModel_ = state.pModel_;
	tex_ = state.tex_;

	keys_ = YInput::Keys::GetInstance();
}

void Player::Initialize(const YGame::Transform::Status& status)
{
	Character::Initialize(
		{ HP, CheatTime }, status,
		{ 0.5f,RisePower,0.0f }, { 3.0f,RisePower,0.0f }
	);

	drawer_.Initialize(&obj_->m_, &direction_);

	Reset(status);
}

void Player::Reset(const YGame::Transform::Status& status)
{
	Character::Reset(
		{ HP, CheatTime }, status
	);
	MapChipCollider::Initialize({ obj_->scale_ });

	drawer_.Reset();

	jumpCount_ = 0;
}

void Player::UpdateMove()
{
	move_.x_ = static_cast<float>(keys_->Horizontal());

	if (move_.x_ > 0)
	{
		direction_ = { +1.0f,0.0f,0.0f };
	}
	else if (move_.x_ < 0)
	{
		direction_ = { -1.0f,0.0f,0.0f };
	}
}

void Player::Jump()
{
	if (++jumpCount_ > MaxJumpCount) { return; }
	jumpCount_ = min(jumpCount_, MaxJumpCount);

	Character::Jump();
}

void Player::Update()
{
	if (keys_->IsTrigger(DIK_SPACE))
	{
		if (isChanged_)
		{
			//YGame::WorldRuler::GetInstance()->SetTimeSpeed(1.0f);
			isChanged_ = false;
		}
		else
		{
			//YGame::WorldRuler::GetInstance()->SetTimeSpeed(0.0f);
			isChanged_ = true;
		}

		drawer_.Initialize(&obj_->m_, &direction_);
	}

	UpdateMove();
	if (keys_->IsTrigger(DIK_W)) { Jump(); }
	UpdatePhysics();

	if (IsLanding())
	{
		jumpCount_ = 0;
	}

	Character::Update();

	obj_->UpdateMatrix(
		{
			{},
			{},
			//SlimeActor::JiggleValue()
		}
	);

	drawer_.Update();
}

void Player::Draw()
{
	drawer_.Draw();
}

void Player::Draw2D()
{
}

