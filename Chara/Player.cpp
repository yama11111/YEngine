#include "Player.h"
#include "CharaConfig.h"
#include "CollisionConfig.h"
#include "CalcTransform.h"
#include "YMath.h"
#include <cassert>

#pragma region –¼‘O‹óŠÔ
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
			Collision::Attribute::Player,
			Collision::Attribute::Enemy
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
	InitializeSlimeAct();

	jumpCount_ = 0;
}

void Player::OnCollision(const uint32_t attribute, const YMath::Vec3& pos)
{
	if (attribute == Collision::Attribute::Enemy)
	{
		// “¥‚ñ‚¾‚È‚ç
		if (obj_.pos_.y_ - pos.y_ >= CharaConfig::AttackRange)
		{
			UpdateJump();
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

	UpdateJump();
}
void Player::UpdateJump()
{
	speed_.y_ = RisePower;

	Vec3 val = obj_.scale_ * CharaConfig::SlimeAct::ElasticityValue;
	val.y_ *= -1.0f;

	Vec3 squash  = +val;
	Vec3 streach = -val;

	ActivateSlimeAct({ squash, streach }, CharaConfig::SlimeAct::Frame);
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

	UpdateCharaStatus();
	obj_.color_.g_ = (1.0f - isCheat() * 1.0f);
	obj_.color_.b_ = (1.0f - isCheat() * 1.0f);
	obj_.color_.a_ = (1.0f - isCheat() * 0.5f);

	UpdateSlimeAct();

	obj_.UniqueUpdate({ {}, {}, SlimeActValue()});
}

void Player::Draw(const YGame::ViewProjection& vp)
{
	pModel_->Draw(obj_, vp, tex_);
}

