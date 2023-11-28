#include "GameCamera.h"
#include "MathUtil.h"
#include "MathVector.h"
#include "Lerp.h"

using YGame::GameCamera;
using YMath::Vector3;
using YMath::Power;
using YMath::Lerp;

void GameCamera::Initialize()
{
	camera_.Initialize({}, {});

	target_ = Vector3(+32.0f, -12.0f, +64.0f);
	distance_ = Vector3(-6.0f, +4.0f ,-40.0f);

	elderPlayerPos_ = {};

	moveOnJumpSets_.clear();
}

void GameCamera::Update()
{
	if (pPlayerPos_ == nullptr) { return; }
	
	// 終了していたら削除
	moveOnJumpSets_.remove_if([](MoveOnJumpSet& set) { return set.isAlive == false; });

	// 積まれたジャンプ時移動を加算していく
	float moveYVal = 0.0f;
	for (MoveOnJumpSet& set : moveOnJumpSets_)
	{
		set.power.Update(set.isActPower);
		
		if (set.isActPower)
		{
			moveYVal += YMath::EaseOut<float>(0.0f, 10.0f, set.power.Ratio(), 3.0f);
		}
		else
		{
			moveYVal += YMath::EaseOut<float>(0.0f, 10.0f, set.power.Ratio(), 1.2f);
		}

		// 最大値になったら折り返す
		if (set.power.IsMax())
		{
			if (pPlayerPos_->y_ <= elderPlayerPos_.y_)
			{
				set.isActPower = false;
			}
		}
		// 終了処理
		if (set.power.IsZero() && set.isActPower == false)
		{
			set.isAlive = false;
		}
	}

	camera_.pos_ = Vector3(pPlayerPos_->x_, 0, 0) + distance_ + Vector3(0, moveYVal, 0);
	camera_.rota_ = YMath::AdjustAngle(target_.Normalized());

	camera_.Update();

	elderPlayerPos_ = *pPlayerPos_;
}

void GameCamera::MoveOnJump()
{
	if (pPlayerPos_->y_ < -6.0f) { return; }

	MoveOnJumpSet newSet;

	newSet.isAlive = true;
	newSet.isActPower = true;
	newSet.power.Initialize(24);

	moveOnJumpSets_.push_back(newSet);
}

void GameCamera::Shaking(const float swing, const float dekey, const float place)
{
	camera_.Shaking(swing, dekey, place);
}

void GameCamera::SetPlayerPosPtr(YMath::Vector3* pFollowPoint)
{
	pPlayerPos_ = pFollowPoint;
}

YGame::ViewProjection GameCamera::GetViewProjection() const
{
	return camera_.GetViewProjection();
}

//void GameCamera::UpdateCenter()  
//{
//	if (pPlayerPos_ == nullptr) { return; }
//
//	float moveYVal = pPlayerPos_->y_ - elderPlayerPos_.y_;
//
//	// カメラでとらえる範囲の中にいるか
//	bool isOverLower, isOverUpper;
//	YMath::InRange<float>(pPlayerPos_->y_, center_.y_ - 6.0f, center_.y_ + 6.0f, isOverLower, isOverUpper);
//	
//	// いないなら調整スピードの速度を上げる
//	overLowerPower_.Update(isOverLower);
//	overUpperPower_.Update(isOverUpper);
//	float downSpeed	 = YMath::EaseInOut<float>(0.0f, -0.8f, overLowerPower_.Ratio(), 1.6f);
//	float upSpeed	 = YMath::EaseInOut<float>(0.0f, +0.8f, overUpperPower_.Ratio(), 1.6f);
//	float adjustSpeed = upSpeed + downSpeed;
//
//	// どれだけ離れているかでさらに速度上げる
//	//float distanceRatio = std::abs(pFollowPoint_->y_ - (center_.y_ - 2.0f)) * 0.01f;
//	//distanceRatio = YMath::Clamp<float>(distanceRatio, 0.0f, 1.0f);
//	//adjustSpeed *= YMath::Lerp<float>(1.0f, 2.0f, distanceRatio);
//
//	center_.x_ = pPlayerPos_->x_ + 10.0f;
//	center_.y_ += adjustSpeed;
//	
//	elderPlayerPos_ = *pPlayerPos_;
//}
