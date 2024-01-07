#include "GameCamera.h"
#include "MathUtil.h"
#include "MathVector.h"
#include "Lerp.h"
#include <string>
#include <imgui.h>
#include <cmath>

using YGame::GameCamera;
using YMath::Vector3;
using YMath::Power;

namespace
{
	const Vector3 kTarget = Vector3(+32.0f, -12.0f, +64.0f);
	const Vector3 kDistance = Vector3(-4.0f, +12.0f, -40.0f);

	const Vector3 kCameraSpeed = Vector3(2.0f, 0.3f, 0.0f);
	const float kCameraSpeedRate = 0.1f;

	const Vector3 kTargetSpeed = Vector3(1.0f, 1.0f, 1.0f);
	const float kTargetSpeedRate = 0.1f;

	const Vector3 kAccelEndPos = Vector3(-6.0f, +2.0f, -6.0f);
}

void GameCamera::Initialize()
{
	target_ = kTarget;
	distance_ = kDistance;

	camera_.Initialize(distance_, &target_, true);

	accelPower_.Initialize(30);
	isActAccelPower_ = false;
}

void GameCamera::Update()
{
	if (pPlayerPos_ == nullptr) { return; }
	
	UpdatePos();

	accelPower_.Update(isActAccelPower_);
	if (accelPower_.IsMax()) { isActAccelPower_ = false; }
	Vector3 animePos = YMath::EaseOut(Vector3(), kAccelEndPos, accelPower_.Ratio(), 3.0f);

	UpdateTarget();

	camera_.Update({ animePos });
}

void GameCamera::DrawDebugText()
{
	static const std::string windowName = "Camera";

	ImGui::Begin(windowName.c_str());

	ImGui::Text("pos    : %f, %f, %f", camera_.pos_.x_, camera_.pos_.y_, camera_.pos_.z_);
	ImGui::Text("target : %f, %f, %f", target_.x_, target_.y_, target_.z_);

	ImGui::End();
}

void GameCamera::UpdatePos()
{
	// [カメラ → 基準点] * 速さ * 倍率
	Vector3 base = *pPlayerPos_ + distance_;
	Vector3 vectorCameraToBase = base - camera_.pos_;
	Vector3 speed = YMath::MultAtComponent(vectorCameraToBase, kCameraSpeed) * kCameraSpeedRate;

	camera_.pos_ += speed;
}

void GameCamera::UpdateTarget()
{
	// [注視点 → 基準点] * 速さ * 倍率
	Vector3 base = *pPlayerPos_ + kTarget;
	Vector3 vectorTargetToBase = base - target_;
	Vector3 speed = YMath::MultAtComponent(vectorTargetToBase, kTargetSpeed) * kTargetSpeedRate;

	target_ += speed;
}

void GameCamera::MoveOnJump()
{
}

void GameCamera::MoveOnAccel()
{
	isActAccelPower_ = true;
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
