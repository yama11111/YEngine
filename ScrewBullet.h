#pragma once
#include "EnemyBullet.h"
class ScrewBullet : public EnemyBullet
{
private:
	MatWorld parent{};
	Object3D obj2{};
	float rad = 0.0f;
public:
	void Initialize(const Vec3& pos, const Vec3& velocity, Model* model, const UINT tex) override;
	void Update() override;
	void Draw(MatViewProjection& mVP) override;
	Vec3 GetWorldPos() override;
private:
	void Screw();
	void Homing() override;
};

