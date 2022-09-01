#pragma once
#include "Collider.h"
#include <memory>
#include <list>

class CollisionManager {
private:
	std::list<Collider*> colliders;
	std::list<Collider*> colliders2;
public:
	~CollisionManager();
	void Initialize();
	void Update();
	void PushBack(Collider* collider);
	void PushBack2(Collider* collider);
	void Clear();
private:
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
	void CheckAllCollisions();
};
