#pragma once
#include "Enemy.h"
#include "CollisionManager.h"

class EnemyManager
{
public:
	std::list<std::unique_ptr<Enemy>> enemys;
private:
	CollisionManager* collM = nullptr;
public:
	void Initialize(Player* player, Model* model, const UINT plainTex);
	void Update();
	void Collision();
	void Draw(MatViewProjection& mVP);
	void SetCollManager(CollisionManager* collM) { this->collM = collM; }
};

