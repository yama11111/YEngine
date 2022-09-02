#pragma once
#include "MatWorld.h"
#include "MatViewProjection.h"
#include "Speed.h"
#include "Shake.h"

class RailCamera {
private:
	MatWorld mW{};
	MatViewProjection vp{};
	Speed speed{};
	Shake shake{};
	float power = 0.0f;
public:
	void Initialize(const Vec3& pos);
	void Update();
	void Shaking(const float swing, const float dekey);
	Vec3 ShakeValue() { return shake.GetValue(); }
	MatViewProjection GetViewProjection() { return vp; }
	MatViewProjection GetViewProjectionD();
	Mat4* GetMatWorld() { return &mW.m; }
private:
	void Move();
	void Rotate();
	void vpUpdate();
};
