#include "MatView.h"
#include "Calc.h"

using Math::MatView;

MatView::MatView() :
	eye_({ 0.0f, 0.0f, -100.0f }),
	target_({ 0.0f, 0.0f, 0.0f }),
	up_({ 0.0f, 1.0f, 0.0f })
{
	Update();
}

MatView::MatView(const InitStatus& init) :
	eye_(init.eye_), 
	target_(init.target_), 
	up_(init.up_)
{
	Update();
}

void MatView::Initialize(const InitStatus& init)
{
	eye_ = init.eye_; 
	target_ = init.target_;
	up_ = init.up_;
	Update();
}

void MatView::Update()
{
	m_ = MatLookAtLH(eye_, target_, up_);
}
