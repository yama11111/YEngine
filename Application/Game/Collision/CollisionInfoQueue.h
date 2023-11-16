#pragma once
#include "CollisionInfo.h"
#include <array>
#include <queue>

namespace YGame
{	
	class CollisionInfoQueue
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

		/// <summary>
		/// 挿入
		/// </summary>
		/// <param name="index"> : キュー番号</param>
		/// <param name="info"> : 衝突情報</param>
		void PushBack(const size_t index, const CollisionInfo& info);

		/// <summary>
		/// 衝突情報取得
		/// </summary>
		/// <param name="index"> : キュー番号</param>
		/// <returns>衝突情報</returns>
		CollisionInfo Front(const size_t index);
		
		/// <summary>
		/// 先頭削除
		/// </summary>
		/// <param name="index"> : キュー番号</param>
		void Pop(const size_t index);

		/// <summary>
		/// 空フラグ取得
		/// </summary>
		/// <param name="index"> : キュー番号</param>
		/// <returns>空フラグ</returns>
		bool Empty(const size_t index) const;

	public:

		/// <summary>
		/// シングルトン
		/// </summary>
		/// <returns></returns>
		static CollisionInfoQueue* GetInstance();

	private:

		CollisionInfoQueue() = default;
		~CollisionInfoQueue() = default;
		CollisionInfoQueue(const CollisionInfoQueue&) = delete;
		const CollisionInfoQueue& operator=(const CollisionInfoQueue&) = delete;

	private:
	
		// 衝突キュー配列
		std::array<std::queue<CollisionInfo>, 200> collQueues_;

	};
}
