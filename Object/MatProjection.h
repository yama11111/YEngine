#pragma once
#include "Mat4.h"

namespace Object
{
	struct MatProjection
	{
	public:
		Math::Mat4 m;
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
}

