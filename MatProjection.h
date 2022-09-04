#pragma once
#include "Math/Mat4.h"

struct MatProjection
{
public:
	Mat4 m;
public:
	MatProjection();
	enum Projection 
	{
		OrthoGraphic = 0,
		Perspective = 1,
	};
	MatProjection(const int projection);
	void Set(const int projection);
};

