//#include "Player.h"
//#include "CharaConfig.h"
//#include "CollisionConfig.h"
//#include "CalcTransform.h"
//#include "YMath.h"
//#include <cassert>
//
//#pragma region –¼‘O‹óŠÔ
//using YMath::Vec3;
//using CharaConfig::GravityPower;
//using namespace CharaConfig::Player;
//#pragma endregion
//
//YGame::Model* Player::pModel_ = nullptr;
//YGame::Sprite2D* Player::pJump_ = nullptr;
//UINT Player::tex_ = UINT_MAX;
//
//void Player::StaticIntialize(const StaticInitStatus& state)
//{
//	assert(state.pModel_);
//	assert(state.pSprite_);
//
//	pModel_ = state.pModel_;
//	pJump_ = state.pSprite_;
//	tex_ = state.tex_;
//}
//
//void Player::Initialize(const InitStatus& state)
//{
//	InitializeCollisionStatus(
//		{
//			CollRad,
//			YCollision::Attribute::Player,
//			YCollision::Attribute::Enemy
//		}
//	);
//	Reset(state);
//}
//
//void Player::Reset(const InitStatus& state)
//{
//	jump[0].Initialize({ { 960, 512, 0 } });
//	jump[1].Initialize({ { 960 + 160, 512, 0 } });
//
//	InitializeCharacter(
//		{
//			state.pos_,
//			YMath::AdjustAngle(YMath::Vec3(0, 0, 1)),
//			{6.0f,6.0f,6.0f}
//		}
//	);
//	InitializeCharaStatus({ HP, CheatTime });
//	InitializeMapCollisionStatus({obj_.scale_});
//
//	jumpCount_ = 0;
//}
//
//void Player::OnCollision(const uint32_t attribute, const YMath::Vec3& pos)
//{
//	if (attribute == YCollision::Attribute::Enemy)
//	{
//		// “¥‚ñ‚¾‚È‚ç
//		if (obj_.pos_.y_ - pos.y_ >= CharaConfig::AttackRange)
//		{
//			UpdateJump();
//		}
//		else
//		{
//			Hit(1);
//			ActivateHitAction(CharaConfig::HitAct::ShakeValue, CheatTime);
//		}
//	}
//}
//
//void Player::UpdateMove()
//{
//	speed_.z_ = 3.0f;
//	Vec3 d = { 0.0f, 0.0f, -1.0f };
//	pParticleMan_->EmitDust(obj_.pos_, d, 8, 2);
//}
//
//void Player::Jump()
//{
//	if (++jumpCount_ > MaxJumpCount) { return; }
//	jumpCount_ = min(jumpCount_, MaxJumpCount);
//
//	UpdateJump();
//}
//void Player::UpdateJump()
//{
//	speed_.y_ = RisePower;
//
//	Vec3 val = obj_.scale_ * CharaConfig::SlimeAct::ElasticityValue;
//	val.y_ *= -1.0f;
//
//	Vec3 squash  = +val;
//	Vec3 streach = -val;
//
//	ActivateSlimeAction({ {}, squash, streach }, CharaConfig::SlimeAct::Frame);
//}
//
//void Player::Attack()
//{
//	UpdateAttack();
//}
//void Player::UpdateAttack()
//{
//
//}
//
//void Player::Update()
//{
//
//	UpdateMove();
//	UpdateGravity();
//
//	if (IsLanding())
//	{
//		jumpCount_ = 0;
//	}
//
//	obj_.pos_ += speed_;
//
//	if (obj_.pos_.y_ <= -150.0f)
//	{
//		SetHP(0);
//	}
//
//	UpdateCharacter();
//
//	obj_.UpdateMatrix(
//		{
//			HitActionShakeValue(),
//			{},
//			SlimeActionValue()
//		}
//	);
//
//	for (size_t i = 0; i < 2; i++)
//	{
//		//jump[i].color_ = { 1.0f,1.0f,1.0f,1.0f };
//		//if(jumpCount_ > i) 
//		//{
//		//	jump[i].color_ = { 0.1f,0.1f,0.1f,1.0f };
//		//}
//		jump[i].UpdateMatrix();
//	}
//}
//
//void Player::Draw(const YGame::ViewProjection& vp)
//{
//	//pModel_->Draw(obj_, vp);
//}
//
//void Player::Draw2D()
//{
//	for (size_t i = 0; i < 2; i++)
//	{
//		pJump_->Draw(jump[i]);
//	}
//}
//
