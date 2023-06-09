#include "GameObjectCollisionManager.h"
#include <cassert>

using YGame::GameObjectCollisionManager;

void GameObjectCollisionManager::Initialize()
{
	Clear();
}

void GameObjectCollisionManager::Update()
{
	// 誰もいないなら弾く
	if (pColliders_.empty()) { return; }
	
	// 全コライダー判定チェック
	CheckAllCollision();
	
	// 全コライダークリア
	Clear();
}

void GameObjectCollisionManager::PushBack(GameObjectCollider* pCollider)
{
	// nullチェック
	assert(pCollider);
	
	// 挿入
	pColliders_.push_back(pCollider);
}

void GameObjectCollisionManager::Clear()
{
	// 空なら弾く
	if (pColliders_.empty()) { return; }

	// コライダー全削除
	pColliders_.clear();
}

void GameObjectCollisionManager::CheckAllCollision()
{
	// コライダーAの始めから
	std::list<GameObjectCollider*>::iterator itrA = pColliders_.begin();
	
	// 終わりまで
	for (; itrA != pColliders_.end(); ++itrA)
	{
		// ポインタを取得
		GameObjectCollider* colA = *itrA;

		// コライダーAの初め + 1から (コライダーB)
		std::list<GameObjectCollider*>::iterator itrB = itrA;
		itrB++;

		// 終わりまで
		for (; itrB != pColliders_.end(); ++itrB)
		{
			// ポインタを取得
			GameObjectCollider* colB = *itrB;
			
			// 判定チェック
			CheckCollisionPair(colA, colB);
		}
	}
}

void GameObjectCollisionManager::CheckCollisionPair(GameObjectCollider* pColliderA, GameObjectCollider* pColliderB)
{
	// どちらかすり抜けるなら弾く
	if (pColliderA->IsSlip() == true || pColliderB->IsSlip() == true) { return; }

	// 球 と 球 の判定
	if (YGame::CollisionSphereSphere(*pColliderA, *pColliderB))
	{
		// お互いに衝突時判定
		pColliderA->OnCollision(pColliderB);
		pColliderB->OnCollision(pColliderA);
	}
}
