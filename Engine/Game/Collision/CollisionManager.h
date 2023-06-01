#pragma once
#include "BaseCollider.h"
#include <list>

namespace YGame
{
	class CollisionManager
	{
	private:
		// コライダー格納リスト
		std::list<BaseCollider*> pColliders_;
	public:
		// 初期化
		void Initialize();
		// 更新
		void Update();
	public:
		// 格納
		void PushBack(BaseCollider* pCollider);
		// リストクリア
		void Clear();
	private:
		// 全コリジョン確認
		void CheckAllCollision();
	private:
		// アタリ判定(球)
		static void CheckCollisionPair(BaseCollider* pColliderA, BaseCollider* pColliderB);
	};
}
