#include "CameraManager.h"
#include "CalcTransform.h"
#include <cassert>

using YGame::CameraManagerCommon;
using YGame::CameraManager;
using YMath::Vector3;

YInput::Keys* CameraManagerCommon::keys_ = nullptr;
YInput::Mouse* CameraManagerCommon::mouse_ = nullptr;
YInput::Pad* CameraManagerCommon::pad_ = nullptr;

void CameraManagerCommon::StaticInitialize()
{
	keys_ = YInput::Keys::GetInstance();
	mouse_ = YInput::Mouse::GetInstance();
	pad_ = YInput::Pad::GetInstance();
}

void CameraManager::Initialize(const std::vector<InitStatus>& statuses)
{
	pFollowPoint_ = statuses[0].pFollowPoint_;
	camera_.Initialize({}, pFollowPoint_, true);
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
