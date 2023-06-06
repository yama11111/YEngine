#include "ViewProjection.h"
#include "MathVector.h"

using YGame::ViewProjection;

ViewProjection::ViewProjection() :
	eye_({ 0.0f, 0.0f, -100.0f }),
	target_({ 0.0f, 0.0f, 0.0f }),
	up_({ 0.0f, 1.0f, 0.0f }),
	view_(YMath::MatLookAtLH(eye_, target_, up_)),
	pro_(YMath::MatPerspective())
{}

ViewProjection::Status ViewProjection::Status::Default()
{
	// 戻り値用
	Status result;

	// デフォルト値を代入
	result.eye_ = { 0.0f, 0.0f, -100.0f };
	result.target_ = { 0.0f, 0.0f, 0.0f };
	result.up_ = { 0.0f, 1.0f, 0.0f };

	// 返す
	return result;
}

void ViewProjection::Initialize(const Status& status)
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
