#include "MatViewProjection.h"

MatViewProjection::MatViewProjection() :
	view(MatView()), pro(MatProjection(MatProjection::Perspective))
{
}

void MatViewProjection::Update()
{
	view.Update();
}
