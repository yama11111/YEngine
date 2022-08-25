#pragma once
#include "Collider.h"
#include <memory>
#include <list>

class CollisionManager {
private:
	std::list<Collider*> colliders;
public:
	~CollisionManager();
	void Initialize();
	void Update();
	void PushBack(Collider* collider);
	void Clear();
private:
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
	void CheckAllCollisions();
};
