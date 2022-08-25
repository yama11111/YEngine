#pragma once
#include "Collider.h"
#include "Model.h"

class PlayerBullet : public Collider 
{
private:
	Object3D obj{};
	Model* model = nullptr;
	Vec3 velocity{};
	static const int32_t LIFE_T = 60 * 5;
	int32_t deathT = LIFE_T;
	bool isDead = false;
	UINT tex = 0;
public:
	void Initialize(Model* model, const Vec3& pos, const Vec3& velocity, const UINT tex);
	void Update();
	void Draw(MatViewProjection& mVP);
	bool IsDead() const { return isDead; }
	void OnCollision() override;
	Vec3 GetWorldPos() override;
};
