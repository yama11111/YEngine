#pragma once
#include "EnemyBullet.h"
class CircleBullet : public EnemyBullet
{
private:
	float radian = 0.0f;
	float radius = 0.0f;
public:
	void Initialize2(const Vec3& pos, const Vec3& velocity,
					 const float radius, const float radian, Model* model, const UINT tex) override;
	void Update() override;
	void Draw(MatViewProjection& mVP) override;
	Vec3 GetWorldPos() override;
private:
	void Screw();
};

