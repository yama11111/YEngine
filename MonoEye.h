#pragma once
#include "Enemy.h"

class MonoEye : public Enemy
{
public:
	void Initialize(const Vec3& pos, Model* model, const UINT tex, const UINT bulletTex) override;
	void Update() override;
	void Draw(MatViewProjection& mVP) override;
	void Fire() override;
	void FireAndReset() override;
};

