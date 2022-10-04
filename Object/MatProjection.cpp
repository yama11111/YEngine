#include "MatProjection.h"
#include "Calc.h"

using Object::MatProjection;
using Math::Mat4;

MatProjection::MatProjection() :
	m(Mat4())
{}

MatProjection::MatProjection(const int projection)
{
	switch (projection)
	{
	case OrthoGraphic:
		m = Math::MatOrthoGraphic();
		break;
	case Perspective:
		m = Math::MatPerspective();
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
		m = Math::MatOrthoGraphic();
		break;
	case Perspective:
		m = Math::MatPerspective();
		break;
	default:
		m = Mat4();
		break;
	}
}
