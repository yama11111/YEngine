#include "CollisionManager.h"
#include <cassert>

using YGame::CollisionManager;
using YMath::Vector3;

void CollisionManager::Initialize() 
{
	Clear();
}

void CollisionManager::Update() 
{
	if (pColliders_.empty()) { return; }
	CheckAllColliders();
	Clear();
}

void CollisionManager::PushBack(Collider* pCollider) 
{
	assert(pCollider);
	pColliders_.push_back(pCollider); 
}

void CollisionManager::Clear() 
{
	if (pColliders_.empty()) { return; }
	pColliders_.clear();
}

void CollisionManager::CheckAllColliders() 
{
	std::list<Collider*>::iterator itrA = pColliders_.begin();
	for (; itrA != pColliders_.end(); ++itrA) 
	{
		Collider* colA = *itrA;

		std::list<Collider*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != pColliders_.end(); ++itrB) 
		{
			Collider* colB = *itrB;
			CheckCollisionPair(colA, colB);
		}
	}
}

void CollisionManager::CheckCollisionPair(Collider* pColliderA, Collider* pColliderB)
{
	// 属性マスク判定
	bool isAct1 = (pColliderA->Attribute() & pColliderB->Mask()) == 0 || (pColliderB->Attribute() & pColliderA->Mask()) == 0;
	// すり抜けフラグ確認
	bool isAct2 = pColliderA->IsSlip() || pColliderB->IsSlip();

	if (isAct1 || isAct2) { return; }

	Vector3 posA = pColliderA->Pos();
	Vector3 posB = pColliderB->Pos();
	Vector3 dist = posB - posA;

	if (dist.Length() <= pColliderA->Radius() + pColliderB->Radius())
	{
		pColliderA->OnCollision(pColliderB->Attribute(), pColliderB->Pos());
		pColliderB->OnCollision(pColliderA->Attribute(), pColliderA->Pos());
	}
}