#include "Player.h"
#include "CharaConfig.h"
#include "CollisionConfig.h"
#include "CalcTransform.h"
#include "YMath.h"
#include <cassert>

#pragma region ���O���
using YMath::Vec3;
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
			YCollision::Attribute::Player,
			YCollision::Attribute::Enemy
		}
	);
	Reset(state);
}

void Player::Reset(const InitStatus& state)
{
	InitializeCharacter(
		{
			state.pos_,
			YMath::AdjustAngle(YMath::Vec3(0, 0, 1)),
			{5.0f,5.0f,5.0f}
		}
	);
	InitializeCharaStatus({ HP, CheatTime });
	InitializeMapCollisionStatus({obj_.scale_});

	jumpCount_ = 0;
}

void Player::OnCollision(const uint32_t attribute, const YMath::Vec3& pos)
{
	if (attribute == YCollision::Attribute::Enemy)
	{
		// ���񂾂Ȃ�
		if (obj_.pos_.y_ - pos.y_ >= CharaConfig::AttackRange)
		{
			UpdateJump();
		}
		else
		{
			Hit(1);
			ActivateHitAction(CharaConfig::HitAct::ShakeValue, CheatTime);
		}
	}
}

void Player::Jump()
{
	if (++jumpCount_ > MaxJumpCount) { return; }
	jumpCount_ = min(jumpCount_, MaxJumpCount);

	UpdateJump();
}
void Player::UpdateJump()
{
	speed_.y_ = RisePower;

	Vec3 val = obj_.scale_ * CharaConfig::SlimeAct::ElasticityValue;
	val.y_ *= -1.0f;

	Vec3 squash  = +val;
	Vec3 streach = -val;

	ActivateSlimeAction({ squash, streach }, CharaConfig::SlimeAct::Frame);
}

void Player::Attack()
{
	UpdateAttack();
}
void Player::UpdateAttack()
{

}

void Player::Update()
{
	UpdateGravity();

	if (IsLanding())
	{
		jumpCount_ = 0;
	}

	obj_.pos_ += speed_;

	if (obj_.pos_.y_ <= -150.0f)
	{
		SetHP(0);
	}

	UpdateCharacter();

	obj_.UniqueUpdate(
		{
			HitActionShakeValue(),
			{},
			SlimeActionValue()
		}
	);
}

void Player::Draw(const YGame::ViewProjection& vp)
{
	pModel_->Draw(obj_, vp, tex_);
}

