#pragma once
#include "BasePrimitiveCollider.h"

namespace YMath
{
	// 球
	class SphereCollider final :
		public BasePrimitiveCollider
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint,
			const float radius,
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const float radius,
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
		/// 中心点
		/// </summary>
		/// <returns>中心点</returns>
		YMath::Vector3 Center() const;

		/// <summary>
		/// 半径
		/// </summary>
		/// <returns>半径</returns>
		inline float Radius() const { return radius_; }

	public:

		SphereCollider() = delete;

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		SphereCollider(
			Vector3* pFollowPoint,
			const float radius,
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		SphereCollider(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const float radius,
			const Vector3& offset = {},
			const bool isPushBack = false,
			const bool isSlip = false);

		virtual ~SphereCollider() = default;

	protected:

		// 半径
		float radius_ = 0.0f;

	protected:

		// 線 × 球
		bool CheckConcreteCollision(const RayCollider& other) const override;

		// 平面 × 球
		bool CheckConcreteCollision(const PlaneCollider& other) const override;

		// 三角形 × 球
		bool CheckConcreteCollision(const TriangleCollider& other) const override;

		// 球 × 球
		bool CheckConcreteCollision(const SphereCollider& other) const override;

	};
}
