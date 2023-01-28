#include "CameraManager.h"
#include "CalcTransform.h"
#include <cassert>

using YMath::Vec3;

void CameraManager::Initialize()
{
	//camera_.Initialize({ {200.0f, -20.0f, 115.0f}, {0.0f, -PI / 2.0f, 0.0f} });
	camera_.Initialize({ {}, { PI / 16.0f, -PI / 3.0f, 0.0f } });
	isFollow_ = true;
	Update();
}

void CameraManager::UpdateFollow()
{
	if (pFollowPoint_ == nullptr) { return; }

	Vec3 p = Vec3(+150.0f, -10.0f, -40.0f + pFollowPoint_->z_);
	camera_.pos_ = p;
}

void CameraManager::Update()
{
	UpdateFollow();
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

void CameraManager::SetFollowPoint(YMath::Vec3* pFollowPoint)
{
	assert(pFollowPoint);
	pFollowPoint_ = pFollowPoint;
}
