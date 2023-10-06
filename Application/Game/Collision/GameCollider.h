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
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="attribute"> : 属性</param>
		/// <param name="mask"> : マスク</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		/// <param name="isClear"> : リストをクリアするか</param>
		void Initialize(
			Transform* pParent, 
			const AttributeType attribute, const AttributeType mask, 
			const bool isSlip = false,
			const bool isClear = false);

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="pOther">相手ポインタ</param>
		bool CheckCollision(GameCollider* pOther);

		/// <summary>
		/// コライダー挿入
		/// </summary>
		/// <param name="collider">コライダー (動的インスタンス)</param>
		void PushBack(YMath::BasePrimitiveCollider* collider);

		/// <summary>
		/// デバッグテキスト本文
		/// </summary>
		virtual void DrawDebugTextContent() override;

	public:

		/// <summary>
		/// コライダーリスト取得
		/// </summary>
		/// <returns>コライダーリスト</returns>
		inline const std::list<std::unique_ptr<YMath::BasePrimitiveCollider>>& Colliders() const { return colliders_; }

		/// <summary>
		/// 属性取得
		/// </summary>
		/// <returns>属性</returns>
		inline AttributeType Attribute() const { return attribute_; }

		/// <summary>
		/// マスク取得
		/// </summary>
		/// <returns>マスク</returns>
		inline AttributeType Mask() const { return mask_; }

		/// <summary>
		/// すり抜けフラグ取得
		/// </summary>
		/// <returns>すり抜けフラグ</returns>
		inline  bool IsSlip() const { return isSlip_; }
	
	public:

		/// <summary>
		/// 親ポインタ設定
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		inline void SetParent(Transform* pParent) { pParent_ = pParent; }

		/// <summary>
		/// すり抜けフラグ設定
		/// </summary>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		inline void SetIsSlip(const bool isSlip) { isSlip_ = isSlip; }

	public:

		GameCollider() = default;

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="attribute"> : 属性</param>
		/// <param name="mask"> : マスク</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		GameCollider(
			Transform* pParent, 
			const AttributeType attribute, const AttributeType mask,
			const bool isSlip = false);

		virtual ~GameCollider() = default;

	private:

		// 親ポインタ
		Transform* pParent_ = nullptr;

		// 属性 (自分)
		AttributeType attribute_ = AttributeType::eAll;

		// マスク (相手)
		AttributeType mask_ = AttributeType::eAll;

		// すり抜けフラグ
		bool isSlip_ = false;

		// プリミティブコライダーリスト
		std::list<std::unique_ptr<YMath::BasePrimitiveCollider>> colliders_;
	};
}
