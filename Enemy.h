#pragma once
#include "Status.h"
#include "EnemyBullet.h"
#include "TimedCall.h"
#include "Collider.h"
#include "Shake.h"
#include <memory>
#include <list>

class Player;

class Enemy : public Collider 
{
public:
	float seekRad = 0.0f;
protected:
	Object3D obj{};
	Status status{};
	bool isDead = false;
	Shake shake{};

	std::list<std::unique_ptr<EnemyBullet>> bullets;
	std::list<std::unique_ptr<TimedCall>> timedCalls;

	Player* player = nullptr;

	Object3D draw{};
	Model* model = nullptr;
	UINT tex = 0;
public:
	virtual void Initialize(const Vec3& pos, Model* model, const UINT tex) = 0;
	virtual void ModelInit() = 0;
	virtual void Update() = 0;
	virtual void Draw(MatViewProjection& mVP) = 0;

	void SetPlayer(Player* player) { this->player = player; }
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets; }

	Vec3 GetWorldPos() override;
	void OnCollision(const int damage) override;

	void HitAnimation();
	void DeathAnimation();
	Object3D GetObjD();
	bool IsDead() { return isDead; }

	virtual void Fire() = 0;
	virtual void FireAndReset() = 0;

	void SetPos(const Vec3& pos) { this->obj.mW.pos = pos; }
	//virtual void Natulal() = 0;

	void FollowEyes();
	void SetTarget();
};
