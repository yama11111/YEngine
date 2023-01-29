#include "Camera.h"
#include "CalcTransform.h"
#include <cassert>

using YCamera::Camera;
using YMath::Vec3;
using YMath::MultVec3Mat4;

void Camera::Initialize(const InitStatus& state)
{
	//shake_.Initialize();
	//pos_ = state.objState_.pos_;
	//rota_ = state.objState_.rota_;
	//obj_.Initialize(state.objState_);
	//vp_.Initialize({});

	pFollowPoint_ = state.pFollowPos_;
	SetIsFollow(state.isFollow_);

	Update();
}

void Camera::UpdateTarget()
{
	if (isFollow_ && 
		vp_.eye_ != *pFollowPoint_)
	{
		vp_.target_ = *pFollowPoint_;
	}
	else
	{
		//Vec3 forward = MultVec3Mat4(Vec3(0, 0, 1), obj_.m_);
		//vp_.target_ = vp_.eye_ + forward;
	}
}
void Camera::Update()
{
	//obj_.pos_ = pos_;
	//obj_.rota_ = rota_;

	//obj_.Update();
	//shake_.Update();

	//// 視点
	//vp_.eye_ = obj_.pos_;
	//// 注視点
	//UpdateTarget();
	//// 上方向ベクトル
	//vp_.up_ = MultVec3Mat4(Vec3(0, 1, 0), obj_.m_);

	//vp_.Update();
}

void Camera::Shaking(const int swing, const int dekey)
{
	shake_.Activate(swing, dekey);
}

YGame::ViewProjection Camera::GetViewProjection()
{
	YGame::ViewProjection result = vp_;
	result.eye_ += shake_.Value() / 10.0f;
	result.target_ += shake_.Value() / 10.0f;
	result.Update();

	return result;
}

Vec3 Camera::Direction()
{
	//Vec3 vel = MultVec3Mat4(Vec3(0, 0, 1), obj_.m_);
	//return vel.Normalized();
	return {};
}

void Camera::SetFollowPoint(YMath::Vec3* pFollowPoint, const bool isFollow)
{
	assert(pFollowPoint);
	pFollowPoint_ = pFollowPoint;
	isFollow_ = isFollow;
}

void Camera::SetIsFollow(const bool isFollow)
{
	if (pFollowPoint_) { isFollow_ = isFollow_; }
	else { isFollow_ = false; }
}
