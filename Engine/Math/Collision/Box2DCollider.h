#pragma once
#include "Vector2.h"
#include "BasePrimitiveCollider.h"

namespace YMath
{
	// 四角形 [2D]
	class Box2DCollider final :
		public BasePrimitiveCollider
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="rectSize"> : 半径</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint,
			const Vector2& rectSize,
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="rectSize"> : 半径</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const Vector2& rectSize,
			const Vector3& offset = {},
			const bool isPushBack = false,
			const bool isSlip = false);

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="other"> : 相手</param>
		/// <returns>衝突したか</returns>
		bool CheckCollision(const BasePrimitiveCollider& other) override;

	public:

		/// <summary>
		/// 中心座標
		/// </summary>
		/// <returns></returns>
		YMath::Vector2 Center() const;

		/// <summary>
		/// 半径
		/// </summary>
		/// <returns>半径</returns>
		inline YMath::Vector2 RectSize() const { return rectSize_; }

	public:

		Box2DCollider() = delete;

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="rectSize"> : 半径</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		Box2DCollider(
			Vector3* pFollowPoint,
			const Vector2& rectSize,
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="rectSize"> : 半径</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		Box2DCollider(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const Vector2& rectSize,
			const Vector3& offset = {},
			const bool isPushBack = false,
			const bool isSlip = false);

		virtual ~Box2DCollider() = default;

	protected:

		// 半径
		YMath::Vector2 rectSize_ = { 0.0f,0.0f };

	protected:

		// 四角形[2D] × 四角形[2D]
		bool CheckConcreteCollision(const Box2DCollider& other) const override;

		bool CheckConcreteCollisionAndPushBack(Box2DCollider& other) const override;

	};
}