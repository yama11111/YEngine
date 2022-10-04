#pragma once
#include "Vec3.h"
#include "Mat4.h"

namespace Object
{
	struct MatView
	{
	public:
		Math::Mat4 m;
		Math::Vec3 eye;
		Math::Vec3 target;
		Math::Vec3 up;
	public:
		MatView();
		struct InitStatus
		{
			Math::Vec3 eye;
			Math::Vec3 target;
			Math::Vec3 up;
		};
		MatView(const InitStatus& init);
		void Update();
	};
}
