#include "MatProjection.h"
#include "Calc.h"

MatProjection::MatProjection() :
	m(Mat4())
{
}

MatProjection::MatProjection(const int projection)
{
	switch (projection)
	{
	case OrthoGraphic:
		m = MatOrthoGraphic();
		break;
	case Perspective:
		m = MatPerspective();
		break;
	default:
		m = Mat4();
		break;
	}
}

void MatProjection::Set(const int projection)
{
	switch (projection)
	{
	case OrthoGraphic:
		m = MatOrthoGraphic();
		break;
	case Perspective:
		m = MatPerspective();
		break;
	default:
		m = Mat4();
		break;
	}
}
