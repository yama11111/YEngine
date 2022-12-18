#include "Camera.h"
#include "CalcTransform.h"

using YMath::Vec3;
using YMath::MultVec3Mat4;

void Camera::Initialize(Game::Object::Status state)
{
	shake_.Initialize();
	SetStatus(state);
}

void Camera::SetStatus(Game::Object::Status state)
{
	pos_ = state.pos_;
	rota_ = state.rota_;
	obj_.Initialize(state);
	vp_.Initialize({});
	Update();
}

void Camera::Shaking(const int swing, const int dekey)
{
	shake_.Activate(swing, dekey);
}

void Camera::Update()
{
	obj_.pos_ = pos_;
	obj_.rota_ = rota_;

	obj_.Update();
	shake_.Update();

	// 視点
	vp_.eye_ = obj_.pos_;
	// 注視点
	Vec3 forward = MultVec3Mat4(Vec3(0, 0, 1), obj_.m_);
	vp_.target_ = vp_.eye_;
	vp_.target_ += forward;
	// 上方向ベクトル
	vp_.up_ = MultVec3Mat4(Vec3(0, 1, 0), obj_.m_);

	vp_.Update();
}

Game::ViewProjection Camera::GetViewProjection()
{
	Game::ViewProjection result = vp_;
	result.eye_ += shake_.Value() / 10.0f;
	result.target_ += shake_.Value() / 10.0f;
	result.Update();

	return result;
}

Vec3 Camera::Verocity()
{
	Vec3 vel = MultVec3Mat4(Vec3(0, 0, 1), obj_.m_);
	//Math::Vec3 vel = Math::MatTransform(Math::Vec3(0, 0, 1), obj_.m_);
	return vel.Normalized();
}
