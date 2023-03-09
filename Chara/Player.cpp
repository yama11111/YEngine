#include "Player.h"
#include "CharaConfig.h"
#include "CollisionConfig.h"
#include "CalcTransform.h"
#include "YMath.h"
#include <cassert>

#pragma region –¼‘O‹óŠÔ
using YMath::Vector3;
using YGame::BaseObject;
using CharaConfig::GravityPower;
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

void Player::Initialize(const YGame::BaseObject::Status& state)
{
	Reset(state);
}

void Player::Reset(const YGame::BaseObject::Status& state)
{
	Character::Initialize(
		{ HP, CheatTime },
		state
	);
	MapChipCollider::Initialize({ obj_->scale_ });

	jumpCount_ = 0;
}

void Player::UpdateMove()
{
	speed_.x_ = 3.0f * keys_->Horizontal();

	if (speed_.x_ > 0)
	{
		direction_.x_ = 1.0f;
	}
	else if (speed_.x_ < 0)
	{
		direction_.x_ = -1.0f;
	}
}

void Player::Jump()
{
	if (++jumpCount_ > MaxJumpCount) { return; }
	jumpCount_ = min(jumpCount_, MaxJumpCount);

	Character::Jump(RisePower);
}

void Player::Update()
{
	UpdateMove();
	if (keys_->IsTrigger(DIK_SPACE)) { Jump(); }
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
			SlimeActor::JiggleValue()
		}
	);
}

void Player::Draw(const YGame::ViewProjection& vp, YGame::LightGroup* lightGroup)
{
	pModel_->Draw(obj_.get(), vp, lightGroup, color_.get(), tex_);
}

void Player::Draw2D()
{
}

