#include "CollisionManager.h"

CollisionManager::~CollisionManager() { Clear(); }

void CollisionManager::Initialize() {}

void CollisionManager::Update() { CheckAllCollisions(); }

void CollisionManager::PushBack(Collider* collider) { colliders.push_back(collider); }

void CollisionManager::Clear() 
{
	if (!colliders.empty()) colliders.clear();
}

void CollisionManager::CheckCollisionPair(Collider* colliderA, Collider* colliderB) 
{
	if ((colliderA->GetAttribute() & colliderB->GetMask()) == 0 ||
		(colliderB->GetAttribute() & colliderA->GetMask()) == 0) 
	{
		return;
	}
	Vec3 posA = colliderA->GetWorldPos();
	Vec3 posB = colliderB->GetWorldPos();
	Vec3 dist = posB - posA;
	if (dist.Length() <= colliderA->GetRad() + colliderB->GetRad()) 
	{
		colliderA->OnCollision(colliderB->GetDamage());
		colliderB->OnCollision(colliderA->GetDamage());
	}
}

void CollisionManager::CheckAllCollisions() 
{
	std::list<Collider*>::iterator itrA = colliders.begin();
	for (; itrA != colliders.end(); ++itrA) 
	{
		Collider* colA = *itrA;

		std::list<Collider*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != colliders.end(); ++itrB) 
		{
			Collider* colB = *itrB;
			CheckCollisionPair(colA, colB);
		}
	}
}
