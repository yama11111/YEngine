//#include "Slime.h"
//#include "CharaConfig.h"
//#include "CollisionConfig.h"
//#include "CalcTransform.h"
//#include "YMath.h"
//#include <cassert>
//
//#pragma region –¼‘O‹óŠÔ
//using CharaConfig::GravityPower;
//using CharaConfig::Enemy::CheatTime;
//using namespace CharaConfig::Enemy::Slime;
//#pragma endregion
//
//YGame::Model* Slime::pModel_ = nullptr;
//UINT Slime::tex_ = UINT_MAX;
//
//void Slime::StaticIntialize(const StaticInitStatus& state)
//{
//	assert(state.pModel_);
//	pModel_ = state.pModel_;
//	tex_ = state.tex_;
//}
//
//void Slime::Initialize(const InitStatus& state)
//{
//	InitializeCollisionStatus(
//		{
//			CollRad,
//			YCollision::Attribute::Enemy,
//			YCollision::Attribute::Player
//		}
//	);
//	Reset(state);
//}
//
//void Slime::Reset(const InitStatus& state)
//{
//	InitializeCharacter(
//		{
//			state.pos_,
//			YMath::AdjustAngle(YMath::Vec3(0, 0, -1)),
//			{10.0f,10.0f,10.0f}
//		}
//	);
//	InitializeCharaStatus({ HP, CheatTime });
//	InitializeMapCollisionStatus({ obj_.scale_ });
//}
//
//void Slime::Update()
//{
//	UpdateGravity();
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
//}
//
//void Slime::Draw(const YGame::ViewProjection& vp)
//{
//	//pModel_->Draw(obj_, vp, tex_);
//}
