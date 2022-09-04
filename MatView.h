#pragma once
#include "Math/Vec3.h"
#include "Math/Mat4.h"

struct MatView
{
public:
	Mat4 m;
	Vec3 eye;
	Vec3 target;
	Vec3 up;
public:
	MatView();
	struct InitStatus
	{
		Vec3 eye;
		Vec3 target;
		Vec3 up;
	};
	MatView(const InitStatus& init);
	void Update();
};

