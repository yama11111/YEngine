#pragma once
#include "Vec3.h"
#include "Mat4.h"

namespace Object
{
	struct MatWorld
	{
	public:
		Math::Mat4 m;
		Math::Vec3 pos;
		Math::Vec3 rota;
		Math::Vec3 scale;
	public:
		MatWorld();
		struct InitStatus
		{
			Math::Vec3 pos = { 0.0f, 0.0f, 0.0f };
			Math::Vec3 rota = { 0.0f, 0.0f, 0.0f };
			Math::Vec3 scale = { 1.0f, 1.0f, 1.0f };
		};
		MatWorld(const InitStatus& init);
		void Update();
	};
}
