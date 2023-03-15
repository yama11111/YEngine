#include "CameraManager.h"
#include "CalcTransform.h"
#include <cassert>

using YGame::CameraManager;
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

void CameraManager::Initialize(YMath::Vector3* pFollowPoint)
{
	pFollowPoint_ = pFollowPoint;
	camera_.Initialize({ {}, pFollowPoint, true });
	Update();
}

void CameraManager::Update()
{
	camera_.pos_ = *pFollowPoint_ + Vector3(0.0f, 0.0f, -250.0f);
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
