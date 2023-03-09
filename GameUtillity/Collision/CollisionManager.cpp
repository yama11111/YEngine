#include "CollisionManager.h"
#include "CollisionPrimitive.h"
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
	CheckAllCollision();
	Clear();
}

void CollisionManager::PushBack(BaseCollider* pCollider) 
{
	assert(pCollider);
	pColliders_.push_back(pCollider); 
}

void CollisionManager::Clear() 
{
	if (pColliders_.empty()) { return; }
	pColliders_.clear();
}

void CollisionManager::CheckAllCollision() 
{
	std::list<BaseCollider*>::iterator itrA = pColliders_.begin();
	for (; itrA != pColliders_.end(); ++itrA) 
	{
		BaseCollider* colA = *itrA;

		std::list<BaseCollider*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != pColliders_.end(); ++itrB) 
		{
			BaseCollider* colB = *itrB;
			CheckCollisionPair(colA, colB);
		}
	}
}

void CollisionManager::CheckCollisionPair(BaseCollider* pColliderA, BaseCollider* pColliderB)
{
	// �����}�X�N����
	bool isAct1 = (pColliderA->GetAttribute() & pColliderB->GetMask()) == 0 || (pColliderB->GetAttribute() & pColliderA->GetMask()) == 0;
	// ���G�t���O�m�F
	bool isAct2 = pColliderA->GetIsInvincible() || pColliderB->GetIsInvincible();

	if (isAct1 || isAct2) { return; }

	// �� �~ ��
	if (pColliderA->GetShapeType() == ShapeType::CollsionShapeSphere && 
		pColliderB->GetShapeType() == ShapeType::CollsionShapeSphere)
	{
		Sphere* sphereA = dynamic_cast<Sphere*>(pColliderA);
		Sphere* sphereB = dynamic_cast<Sphere*>(pColliderB);

		if (CollisionSphereSphere(*sphereA, *sphereB))
		{
			pColliderA->OnCollision({ pColliderB });
			pColliderB->OnCollision({ pColliderA });
		}
	}
}