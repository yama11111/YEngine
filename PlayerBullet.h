#pragma once
#include "Collider.h"
#include "Model.h"

class PlayerBullet : public Collider 
{
private:
	Object3D obj{};
	Vec3 velocity{};

	bool charge = false;
	static const int32_t LIFE_T = 60 * 3;
	int32_t deathT = LIFE_T;
	bool isDead = false;

	Model* model = nullptr;
	UINT tex = 0;
public:
	void Initialize(const Vec3& pos, const Vec3& velocity, const bool charge, 
					Model* model, const UINT tex);
	void Update();
	void Draw(MatViewProjection& mVP);
	bool IsDead() const { return isDead; }
	void OnCollision(const int damange) override;
	Vec3 GetWorldPos() override;
};
