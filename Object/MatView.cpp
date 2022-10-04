#include "MatView.h"
#include "Calc.h"

using Object::MatView;

MatView::MatView() :
	eye(0.0f, 0.0f, -100.0f), 
	target(0.0f, 0.0f, 0.0f), 
	up(0.0f, 1.0f, 0.0f)
{
	m = Math::MatLookAtLH(eye, target, up);
}

MatView::MatView(const InitStatus& init) :
	eye(init.eye), target(init.target), up(init.up)
{
	m = Math::MatLookAtLH(eye, target, up);
}

void MatView::Update()
{
	m = Math::MatLookAtLH(eye, target, up);
}
