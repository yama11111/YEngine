#include "MatViewProjection.h"

using Math::MatViewProjection;

MatViewProjection::MatViewProjection() :
	view_(), pro_(MatProjection::Perspective)
{}

MatViewProjection::MatViewProjection(const MatView::InitStatus& init) :
	view_(init), pro_(MatProjection::Perspective)
{}

void MatViewProjection::Initialize(const MatView::InitStatus& init)
{
	view_.Initialize(init);
	pro_.Initialize(MatProjection::Perspective);
}

void MatViewProjection::Update()
{
	view_.Update();
}
