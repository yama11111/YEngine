#pragma once
#include "Model.h"
class Ray
{
public:
	Object3D obj{};
	Vec3 start;
	Vec3 velocity = { 0,0,1 };
	float length = 1.0f;
	Model* model = nullptr;
	UINT tex = 0;
public:
	struct InitRay
	{
		Vec3 start = { 0,0,0 };
		Vec3 velocity = { 0,0,1 };
		float length = 1.0f;
	};
	void Initialize(const InitRay& init, Model* model, const UINT tex);
	void InitState(const InitRay& init);
	void Update();
	void SetStart(const Vec3& start);
	void SetVelocity(const Vec3& velocity);
	void SetLength(const float length);
	void Draw(MatViewProjection& vP);
	Ray();
private:
	void Adjust();
};
