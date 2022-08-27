#pragma once
#include "Model.h"
class Ray
{
public:
	Object3D obj{};
	Vec3 start;
	Vec3 velocity = { 0,0,1 };
	Model* model = nullptr;
	UINT tex = 0;
public:
	void Initialize(Vec3& start, Vec3& velocity, Model* model, const UINT tex);
	void Update();
	void SetStart(Vec3& start);
	void SetVelocity(Vec3& velocity);
	void Draw(MatViewProjection& vP);
private:
	void Adjust();
};
