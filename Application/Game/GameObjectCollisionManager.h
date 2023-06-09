#pragma once
#include "GameObjectCollider.h"
#include <list>

namespace YGame
{
	class GameObjectCollisionManager
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

	public:

		/// <summary>
		/// 格納
		/// </summary>
		/// <param name="pCollider"> : コライダーポインタ</param>
		void PushBack(GameObjectCollider* pCollider);

		/// <summary>
		/// リストクリア
		/// </summary>
		void Clear();

	private:

		/// <summary>
		/// 全コリジョン確認
		/// </summary>
		void CheckAllCollision();

	private:

		/// <summary>
		/// アタリ判定
		/// </summary>
		/// <param name="pColliderA"> : コライダーポインタA</param>
		/// <param name="pColliderB"> : コライダーポインタB</param>
		static void CheckCollisionPair(GameObjectCollider* pColliderA, GameObjectCollider* pColliderB);

	private:

		// コライダー格納リスト
		std::list<GameObjectCollider*> pColliders_;

	};
}
