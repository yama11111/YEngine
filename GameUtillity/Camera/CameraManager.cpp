#include "CameraManager.h"
#include "CalcTransform.h"
#include <cassert>

using YCamera::CameraManager;
using YMath::Vector3;

YInput::Keys* CameraManager::keys_ = nullptr;
YInput::Mouse* CameraManager::mouse_ = nullptr;
YInput::Pad* CameraManager::pad_ = nullptr;

void CameraManager::StaticInitialize()
{
	keys_ = YInput::Keys::GetInstance();
	mouse_ = YInput::Mouse::GetInstance();
	pad_ = YInput::Pad::GetInstance();
}

void CameraManager::Initialize()
{
	//camera_.Initialize({ {200.0f, -20.0f, 115.0f}, {0.0f, -PI / 2.0f, 0.0f} });
	//camera_.Initialize({ {}, { PI / 16.0f, -PI / 3.0f, 0.0f } });
	//camera_.Initialize({ {{0.0f,+20.0f,-100.0f}} });
	Update();
}

void CameraManager::Update()
{
	camera_.Update();
}

void CameraManager::Shaking(const int swing, const int dekey)
{
	camera_.Shaking(swing, dekey);
}

YGame::ViewProjection CameraManager::GetViewProjection()
{
	return camera_.GetViewProjection();
}

void CameraManager::SetFollowPoint(YMath::Vector3* pFollowPoint)
{
	camera_.SetFollowPoint(pFollowPoint);
}
