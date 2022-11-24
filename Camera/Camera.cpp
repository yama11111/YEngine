#include "Camera.h"
#include "CalcTransform.h"

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
	Math::Vec3 forward = Math::MultVec3Mat4(Math::Vec3(0, 0, 1), obj_.m_);
	vp_.target_ = vp_.eye_;
	vp_.target_ += forward;
	// 上方向ベクトル
	vp_.up_ = Math::MultVec3Mat4(Math::Vec3(0, 1, 0), obj_.m_);

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

Math::Vec3 Camera::Verocity()
{
	Math::Vec3 vel = Math::MultVec3Mat4(Math::Vec3(0, 0, 1), obj_.m_);
	//Math::Vec3 vel = Math::MatTransform(Math::Vec3(0, 0, 1), obj_.m_);
	return vel.Normalized();
}
