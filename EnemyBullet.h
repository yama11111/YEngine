#pragma once
#include "Collider.h"
#include "Model.h"

class Player;

class EnemyBullet : public Collider 
{
protected:
	Object3D obj{};
	Model* model = nullptr;
	Vec3 velocity{};
	float inductive = 0.01f;
	float interval = 1.0f;

	static const int32_t LIFE_T = 60 * 5;
	int32_t deathT = LIFE_T;
	bool isDead = false;
	UINT tex = 0;
	Player* player;
public:
	virtual void Initialize(const Vec3& pos, const Vec3& velocity, Model* model, const UINT tex);
	virtual void Update();
	virtual void Draw(MatViewProjection& mVP);
	bool IsDead() const { return isDead; }
	void SetPlayer(Player* player) { this->player = player; }
	void OnCollision() override;
protected:
	virtual void Homing();
};
