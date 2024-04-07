#include "GameCamera.h"

#include "Lerp.h"
#include "Ease.h"
#include "Power.h"

#include "MathUtil.h"
#include "MathVector.h"

#include <string>
#include <imgui.h>
#include <cmath>
#include <unordered_map>

using YGame::GameCamera;
using YMath::Vector3;
using YMath::Power;

namespace
{
	struct CameraPoint
	{
		// 注視点
		YMath::Vector3 target;
		// 距離
		YMath::Vector3 distance;
	};

	std::unordered_map<GameCamera::Type, const CameraPoint> kPoints =
	{
		{ GameCamera::Type::eNormal, CameraPoint(Vector3(+32.0f, -12.0f, +64.0f), Vector3(-4.0f, +12.0f, -40.0f)) },
		{ GameCamera::Type::ePass, CameraPoint(Vector3(+32.0f, +2.0f, +0.0f), Vector3(-32.0f, +4.0f, +0.0f)) },
	};

	const Vector3 kCameraSpeed = Vector3(2.0f, 0.3f, 0.0f);
	const float kCameraSpeedRate = 0.1f;

	const Vector3 kTargetSpeed = Vector3(1.0f, 1.0f, 1.0f);
	const float kTargetSpeedRate = 0.1f;
}

void GameCamera::Initialize()
{
	type_ = Type::eNormal;

	target_ = kPoints[type_].target;

	camera_.Initialize(kPoints[type_].distance, &target_, true);
}

void GameCamera::Update()
{
	if (pPlayerPos_ == nullptr) { return; }
	
	UpdatePos();

	UpdateTarget();

	camera_.Update();
}

void GameCamera::DrawDebugText()
{
	static const std::string windowName = "Camera";

	ImGui::Begin(windowName.c_str());

	ImGui::Text("pos    : %f, %f, %f", camera_.pos_.x, camera_.pos_.y, camera_.pos_.z);
	ImGui::Text("target : %f, %f, %f", target_.x, target_.y, target_.z);

	ImGui::End();
}

void GameCamera::ChangeType(const Type type)
{
	type_ = type;
}

void GameCamera::UpdatePos()
{
	// [カメラ → 基準点] * 速さ * 倍率
	Vector3 base = *pPlayerPos_ + kPoints[type_].distance;
	Vector3 vectorCameraToBase = base - camera_.pos_;
	Vector3 speed = YMath::MultAtComponent(vectorCameraToBase, kCameraSpeed) * kCameraSpeedRate;

	camera_.pos_ += speed;
}

void GameCamera::UpdateTarget()
{
	// [注視点 → 基準点] * 速さ * 倍率
	Vector3 base = *pPlayerPos_ + kPoints[type_].target;
	Vector3 vectorTargetToBase = base - target_;
	Vector3 speed = YMath::MultAtComponent(vectorTargetToBase, kTargetSpeed) * kTargetSpeedRate;

	target_ += speed;
}

void GameCamera::Shaking(const float swing, const float dekey, const float place)
{
	camera_.Shaking(swing, dekey, place);
}

void GameCamera::SetPlayerPosPtr(YMath::Vector3* pFollowPoint)
{
	pPlayerPos_ = pFollowPoint;
}

Vector3 GameCamera::Pos() const
{
	return camera_.pos_;
}

YGame::ViewProjection GameCamera::GetViewProjection() const
{
	return camera_.GetViewProjection();
}
