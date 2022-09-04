#pragma once
#include "Math/Vec3.h"
#include "Math/Mat4.h"

struct MatWorld
{
public:
	Mat4 m;
	Vec3 pos;
	Vec3 rota;
	Vec3 scale;
public:
	MatWorld();
	struct InitStatus
	{
		Vec3 pos = { 0.0f, 0.0f, 0.0f };
		Vec3 rota = { 0.0f, 0.0f, 0.0f };
		Vec3 scale = { 1.0f, 1.0f, 1.0f };
	};
	MatWorld(const InitStatus& init);
	void Update();
};

