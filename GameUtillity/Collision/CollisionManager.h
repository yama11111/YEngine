#pragma once
#include "Collider.h"
#include <list>

namespace YGame
{
	class CollisionManager
	{
	private:
		// コライダー格納リスト
		std::list<Collider*> pColliders_;
	public:
		// 初期化
		void Initialize();
		// 更新
		void Update();
	public:
		// 格納
		void PushBack(Collider* pCollider);
		// リストクリア
		void Clear();
	private:
		// 全コライダー確認
		void CheckAllColliders();
	private:
		// アタリ判定(球)
		static void CheckCollisionPair(Collider* pColliderA, Collider* pColliderB);
	};
}
