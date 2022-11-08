#include "ViewProjection.h"
#include "Calc.h"

using Object::ViewProjection;

ViewProjection::ViewProjection() :
	eye_({ 0.0f, 0.0f, -100.0f }),
	target_({ 0.0f, 0.0f, 0.0f }),
	up_({ 0.0f, 1.0f, 0.0f }),
	view_(Math::MatLookAtLH(eye_, target_, up_)),
	pro_(Math::MatPerspective())
{}

ViewProjection::ViewProjection(const InitStatus& state) :
	eye_(state.eye_),
	target_(state.target_),
	up_(state.up_),
	view_(Math::MatLookAtLH(eye_, target_, up_)),
	pro_(Math::MatPerspective())
{}

void ViewProjection::Initialize(const InitStatus& state)
{
	eye_ = state.eye_;
	target_ = state.target_;
	up_ = state.up_;
	view_ = Math::MatLookAtLH(eye_, target_, up_);
	pro_ = Math::MatPerspective();
}

void ViewProjection::Update()
{
	view_ = Math::MatLookAtLH(eye_, target_, up_);
}
