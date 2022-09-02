#pragma once
#include "Enemy.h"

class Octos : public Enemy
{
private:
	static const uint32_t ARY = 13;
	Object3D body[ARY];
public:
	void Initialize(const Vec3& pos, Model* model, const UINT tex) override;
	void ModelInit() override;
	void Update() override;
	void Draw(MatViewProjection& mVP) override;
private:
	void Fire() override;
	void FireAndReset() override;
};