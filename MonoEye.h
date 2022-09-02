#pragma once
#include "Enemy.h"

class MonoEye : public Enemy
{
public:
	static const uint32_t ARY = 5;
	Object3D body[ARY];
public:
	void Initialize(const Vec3& pos, Model* model, const UINT tex) override;
	void ModelInit() override;
	void Update() override;
	void Draw(MatViewProjection& mVP) override;
	void Fire() override;
	void FireAndReset() override;
};

