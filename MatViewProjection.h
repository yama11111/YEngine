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
	void Update();
};

