#pragma once
#include "EnemyBullet.h"
#include "TimedCall.h"
#include "Collider.h"
#include <memory>
#include <list>

class Player;

class Enemy : public Collider 
{
public:
	enum class Phase 
	{
		Approach, // 接近する
		Leave,    // 離脱する
	};
	enum Species
	{
		MonoEye = 0,
		WaveAngler = 1,
		Croan = 2,
	};
	float seekRad = 0.0f;
private:
	Object3D obj;
	std::list<std::unique_ptr<EnemyBullet>> bullets;
	Model* model = nullptr;
	Phase phase = Phase::Approach;
	int species = 0;
	std::list<std::unique_ptr<TimedCall>> timedCalls;
	UINT tex = 0;
	UINT bulletTex = 0;
	Player* player = nullptr;
public:
	void Initialize(const Vec3& pos, const int& species, 
		Model* model, const UINT tex, const UINT bulletTex);
	void Update();
	void Draw(MatViewProjection& mVP);
	void SetPlayer(Player* player) { this->player = player; }
	Vec3 GetWorldPos() override;
	void OnCollision(const int damage) override;
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets; }
private:
	void Approach();
	void Leave();
	static void (Enemy::* spUpdateTable[])();
	void Fire();
	void FireAndReset();
};
