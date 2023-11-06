#pragma once
#include "AttributeType.h"
#include "Transform.h"
#include "BasePrimitiveCollider.h"
#include "DebugTextAttacher.h"
#include <list>
#include <memory>
#include <cstdint>

namespace YGame
{
	// ゲーム用コライダークラス
	class GameCollider : 
		public DebugTextAttacher
	{

	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="pOther">相手ポインタ</param>
		bool CheckCollision(GameCollider* pOther);

		/// <summary>
		/// コライダー挿入
		/// </summary>
		/// <param name="attribute"> : 属性</param>
		/// <param name="mask"> : マスク</param>
		/// <param name="collider">コライダー (動的インスタンス)</param>
		void PushBack(
			const AttributeType attribute, const AttributeType mask,
			YMath::BasePrimitiveCollider* collider);

		/// <summary>
		/// デバッグテキスト本文
		/// </summary>
		virtual void DrawDebugTextContent() override;
	
	public:

		/// <summary>
		/// すり抜けフラグ設定
		/// </summary>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		inline void SetIsSlip(const bool isSlip) { isSlip_ = isSlip; }

	public:
		
		/// <summary>
		/// すり抜けフラグ取得
		/// </summary>
		/// <returns>すり抜けフラグ</returns>
		inline  bool IsSlip() const { return isSlip_; }

	public:

		GameCollider() = default;

		virtual ~GameCollider() = default;

	private:
	
		// コライダーセット
		struct ColliderSet
		{			
			// 属性
			AttributeType attribute = AttributeType::eAll;

			// マスク
			AttributeType mask = AttributeType::eAll;

			// プリミティブコライダー
			std::unique_ptr<YMath::BasePrimitiveCollider> collider;
		};

	private:

		// すり抜けフラグ
		bool isSlip_ = false;

		// コライダーリスト
		std::list<std::unique_ptr<ColliderSet>> colliders_;

	private:

		/// <summary>
		/// コライダーリスト取得
		/// </summary>
		/// <returns>コライダーリスト</returns>
		inline const std::list<std::unique_ptr<ColliderSet>>& Colliders() const { return colliders_; }
	};
}
