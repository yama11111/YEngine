#pragma once
#include "EnemyBullet.h"
class SphereBullet : public EnemyBullet
{
private:
public:
	void Initialize(const Vec3& pos, const Vec3& velocity, Model* model, const UINT tex) override;
	void Update() override;
	void Draw(MatViewProjection& mVP) override;
};