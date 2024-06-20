#include "GameCamera.h"

#include "WorldManager.h"

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
using YMath::Matrix4;
using YMath::Power;

namespace
{
	std::unordered_map<GameCamera::Type, const GameCamera::CameraPoint> kPoints =
	{
		{ GameCamera::Type::eInit, GameCamera::CameraPoint(Vector3(), Vector3()) },
		{ GameCamera::Type::eNormal, GameCamera::CameraPoint(Vector3(+32.0f, -12.0f, +64.0f), Vector3(-4.0f, +12.0f, -40.0f)) },
		{ GameCamera::Type::ePass, GameCamera::CameraPoint(Vector3(+32.0f, +2.0f, +0.0f), Vector3(-32.0f, +4.0f, +0.0f)) },
	};
	
	const Vector3 kCameraSpeed = Vector3(2.0f, 0.3f, 0.3f);
	const float kCameraSpeedRate = 1.0f;

	const Vector3 kTargetSpeed = Vector3(1.0f, 1.0f, 1.0f);
	const float kTargetSpeedRate = 1.0f;

	const uint32_t kJumpSpeedFrame = 90;
	const float kJumpSpeedExponent = 1.4f;

	const uint32_t kPointMoveFrame = 240;
	const float kPointMoveExponent = 3.0f;

	const uint32_t kDropFrame = 10;
	const YMath::Ease<float> kDropRatioEas = { 0.0f, 1.5f, 3.0f };
}

void GameCamera::Initialize()
{
	type_ = Type::eNormal;
	elderType_ = Type::eNormal;
	
	point_ = kPoints[Type::eInit];
	pointMoveTim_.Initialize(kPointMoveFrame, true);

	target_ = kPoints[type_].target;

	camera_.Initialize(kPoints[type_].distance, &target_, true);

	cameraPos_ = targetPos_ = playerPos_ = {};

	jumpSpeedRatioTim_.Initialize(kJumpSpeedFrame);
	jumpSpeedRatioTim_.Finish();

	isDrop = false;

	dropAnimePow_.Initialize(kDropFrame);
}

void GameCamera::Update()
{
	pointMoveTim_.Update();
	point_.target = 
		YMath::EaseOut(kPoints[elderType_].target, kPoints[type_].target, pointMoveTim_.Ratio(), kPointMoveExponent);
	point_.distance = 
		YMath::EaseOut(kPoints[elderType_].distance, kPoints[type_].distance, pointMoveTim_.Ratio(), kPointMoveExponent);

	elderPlayerPos_ = playerPos_;
	jumpSpeedRatioTim_.Update();

	UpdatePos();
	
	UpdateTarget();

	dropAnimePow_.Update(isDrop);
	Vector3 vecCameraToPlayer = -camera_.pos_.Normalized();
	Vector3 animePos = vecCameraToPlayer * kDropRatioEas.Out(dropAnimePow_.Ratio());
	isDrop = false;

	camera_.Update({ animePos });
}

void GameCamera::UpdatePos()
{
	// [カメラ → 基準点] * 速さ * 倍率
	Vector3 base = playerPos_ + point_.distance;
	Vector3 vectorCameraToBase = base - cameraPos_;
	Vector3 speed = vectorCameraToBase;
	speed.y *= YMath::EaseIn(0.0f, 1.0f, jumpSpeedRatioTim_.Ratio(), kJumpSpeedExponent);

	cameraPos_ += speed;

	Matrix4 camPosMat =
		YMath::MatTranslation(cameraPos_) *
		WorldManager::GetInstance()->BasePosMat(WorldManager::GetInstance()->CurrentWorldKey());
	camera_.pos_ = YMath::VecTranslation(camPosMat);
}

void GameCamera::UpdateTarget()
{
	// [注視点 → 基準点] * 速さ * 倍率
	Vector3 base = playerPos_ + point_.target;
	Vector3 vectorTargetToBase = base - targetPos_;
	Vector3 speed = vectorTargetToBase;
	//speed.y *= YMath::EaseIn(0.0f, 1.0f, jumpSpeedRatioTim_.Ratio(), kJumpSpeedExponent);

	targetPos_ += speed;

	Matrix4 tarPosMat =
		YMath::MatTranslation(targetPos_) *
		WorldManager::GetInstance()->BasePosMat(WorldManager::GetInstance()->CurrentWorldKey());
	target_ = YMath::VecTranslation(tarPosMat);
}

void GameCamera::ChangeType(const Type type)
{
	pointMoveTim_.Reset(true);
	elderType_ = type_;
	type_ = type;
}

void GameCamera::Shaking(const float swing, const float dekey, const float place)
{
	camera_.Shaking(swing, dekey, place);
}

void GameCamera::PlayAnimation(const AnimationType type)
{
	if (type == AnimationType::eJump)
	{
		jumpSpeedRatioTim_.Reset(true);
	}
	if (type == AnimationType::eDrop)
	{
		isDrop = true;
	}
	else if (type == AnimationType::ePass)
	{
		ChangeType(Type::ePass);
	}
	else if (type == AnimationType::eNormal)
	{
		ChangeType(Type::eNormal);
	}
}

Vector3 GameCamera::Pos() const
{
	return camera_.pos_;
}

YGame::ViewProjection GameCamera::GetViewProjection() const
{
	return camera_.GetViewProjection();
}

void GameCamera::SetPlayerPos(const YMath::Vector3& playerPos)
{
	playerPos_ = playerPos;
}

void GameCamera::DrawDebugText()
{
	static const std::string windowName = "Camera";

	ImGui::Begin(windowName.c_str());

	ImGui::Text("pos    : %f, %f, %f", camera_.pos_.x, camera_.pos_.y, camera_.pos_.z);
	ImGui::Text("target : %f, %f, %f", target_.x, target_.y, target_.z);
	
	ImGui::Text("cameraPos : %f, %f, %f", cameraPos_.x, cameraPos_.y, cameraPos_.z);
	ImGui::Text("targetPos : %f, %f, %f", targetPos_.x, targetPos_.y, targetPos_.z);
	ImGui::Text("playerPos : %f, %f, %f", playerPos_.x, playerPos_.y, playerPos_.z);

	ImGui::End();
}
