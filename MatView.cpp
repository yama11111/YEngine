#include "MatView.h"
#include "Calc.h"

MatView::MatView() :
	eye(0.0f, 0.0f, -100.0f), 
	target(0.0f, 0.0f, 0.0f), 
	up(0.0f, 1.0f, 0.0f)
{
	m = MatLookAtLH(eye, target, up);
}

MatView::MatView(const InitStatus& init) :
	eye(init.eye), target(init.target), up(init.up)
{
	m = MatLookAtLH(eye, target, up);
}

void MatView::Update()
{
	m = MatLookAtLH(eye, target, up);
}
