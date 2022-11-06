#include "MatProjection.h"
#include "Calc.h"
#include <cassert>

using Math::MatProjection;

MatProjection::MatProjection(const int projection)
{
	Initialize(projection);
}

void MatProjection::Initialize(const int projection)
{
	switch (projection)
	{
	case OrthoGraphic:
		m_ = MatOrthoGraphic();
		break;
	case Perspective:
		m_ = MatPerspective();
		break;
	default:
		assert(false);
		break;
	}
}
