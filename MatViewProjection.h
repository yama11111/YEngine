#pragma once
#include "MatView.h"
#include "MatProjection.h"

class MatViewProjection
{
public:
	MatView view;
	MatProjection pro;
public:
	MatViewProjection();
	MatViewProjection(const MatView::InitStatus& init);
	void Update();
};

