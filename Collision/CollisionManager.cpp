#include "CollisionManager.h"
#include <cassert>

using Collision::CollisionManager;

void CollisionManager::Initialize() 
{
	Clear();
}

void CollisionManager::Update() 
{
	CheckAllColliders();
	Clear();
}

void CollisionManager::PushBack(Collider* collider) 
{
	assert(collider);
	colliders_.push_back(collider); 
}

void CollisionManager::Clear() 
{
	if (colliders_.empty()) { return; }
	colliders_.clear();
}

void CollisionManager::CheckAllColliders() 
{
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA) 
	{
		Collider* colA = *itrA;

		std::list<Collider*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != colliders_.end(); ++itrB) 
		{
			Collider* colB = *itrB;
			CheckCollisionPair(colA, colB);
		}
	}
}

void CollisionManager::CheckCollisionPair(Collider* colliderA, Collider* colliderB)
{
	// 属性マスク判定
	bool isAct1 = (colliderA->Attribute() & colliderB->Mask()) == 0 || (colliderB->Attribute() & colliderA->Mask()) == 0;
	// すり抜けフラグ確認
	bool isAct2 = colliderA->IsSlip() || colliderB->IsSlip();

	if (isAct1 || isAct2) { return; }

	Math::Vec3 posA = colliderA->Pos();
	Math::Vec3 posB = colliderB->Pos();
	Math::Vec3 dist = posB - posA;

	if (dist.Length() <= colliderA->Radius() + colliderB->Radius())
	{
		colliderA->OnCollision(colliderB->Mask());
		colliderB->OnCollision(colliderA->Mask());
	}
}