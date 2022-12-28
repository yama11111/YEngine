#include "Player.h"
#include "CharaConfig.h"
#include "CollisionConfig.h"
#include "CalcTransform.h"
#include "MapChipManager.h"
#include "YMath.h"
#include <cassert>

#pragma region –¼‘O‹óŠÔ
using CharaConfig::GravityPower;
using namespace CharaConfig::Player;
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
	InitializeCharaStatus({ HP, CheatTime });

	jumpCount_ = 0;
}

void Player::OnCollision(const uint32_t attribute, const YMath::Vec3& pos)
{
	if (attribute == Collision::Attribute::Enemy)
	{
		// “¥‚ñ‚¾‚È‚ç
		if (obj_.pos_.y_ - pos.y_ >= CharaConfig::AttackRange)
		{
			speed_.y_ = RisePower;
		}
		else
		{
			Hit(1);
		}

	}
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

	if (obj_.pos_.y_ <= -150.0f)
	{
		SetHP(0);
	}

	UpdateCharaStatus();
	obj_.color_.g_ = (1.0f - isCheat() * 1.0f);
	obj_.color_.b_ = (1.0f - isCheat() * 1.0f);
	obj_.color_.a_ = (1.0f - isCheat() * 0.5f);

	obj_.Update();
}

void Player::Draw(const YGame::ViewProjection& vp)
{
	pModel_->Draw(obj_, vp, tex_);
}

