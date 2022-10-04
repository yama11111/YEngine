#include "MatViewProjection.h"

using Object::MatViewProjection;

MatViewProjection::MatViewProjection() :
	view(MatView()), pro(MatProjection(MatProjection::Perspective))
{
}

MatViewProjection::MatViewProjection(const MatView::InitStatus& init) :
	view(MatView(init)), pro(MatProjection(MatProjection::Perspective))
{
}

void MatViewProjection::Update()
{
	view.Update();
}
