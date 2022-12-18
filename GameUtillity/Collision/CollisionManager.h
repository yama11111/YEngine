#pragma once
#include "Collider.h"
#include <memory>
#include <list>

namespace Collision
{
	class CollisionManager
	{
	private:
		// コライダー格納リスト
		std::list<Collider*> colliders_;
	public:
		// 初期化
		void Initialize();
		// 更新
		void Update();
	public:
		// 格納
		void PushBack(Collider* collider);
		// リストクリア
		void Clear();
	private:
		// 全コライダー確認
		void CheckAllColliders();
	private:
		// アタリ判定(球)
		static void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
	};
}
