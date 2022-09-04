#pragma once
#include "Collider.h"
#include "Model.h"
#include "Math/Timer.h"

class Player;

class EnemyBullet : public Collider 
{
protected:
	Object3D obj{};
	MatWorld nucleus{};
	Vec3 velocity{};
	float inductive = 0.0f;
	float speed = 0.0f;

	int32_t deathT = 0;
	bool isDead = false;

	Timer homT{};
	bool isStraight = false;

	Model* model = nullptr;
	UINT tex = 0;
	Player* player;
public:
	virtual void Initialize(const Vec3& pos, const Vec3& velocity, Model* model, const UINT tex);
	virtual void Initialize2(const Vec3& pos, const Vec3& velocity, 
							 const float radius, const float radian, Model* model, const UINT tex);
	virtual void Update() = 0;
	virtual void Draw(MatViewProjection& mVP) = 0;

	bool IsDead() const { return isDead; }
	void SetPlayer(Player* player) { this->player = player; }
	virtual Vec3 GetWorldPos() override;
	void OnCollision(const int damange) override;
protected:
	virtual void Homing();
};
