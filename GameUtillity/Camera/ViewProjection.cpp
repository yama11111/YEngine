#include "ViewProjection.h"
#include "CalcTransform.h"

using YGame::ViewProjection;

ViewProjection::ViewProjection() :
	eye_({ 0.0f, 0.0f, -100.0f }),
	target_({ 0.0f, 0.0f, 0.0f }),
	up_({ 0.0f, 1.0f, 0.0f }),
	view_(YMath::MatLookAtLH(eye_, target_, up_)),
	pro_(YMath::MatPerspective())
{}

void ViewProjection::Initialize(const InitStatus& status)
{
	eye_ = status.eye_;
	target_ = status.target_;
	up_ = status.up_;
	view_ = YMath::MatLookAtLH(eye_, target_, up_);
	pro_ = YMath::MatPerspective();
}

void ViewProjection::UpdateMatrix()
{
	view_ = YMath::MatLookAtLH(eye_, target_, up_);
}
