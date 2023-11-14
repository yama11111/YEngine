#pragma once
#include "BasePrimitiveCollider.h"

namespace YMath
{
	// レイ
	class RayCollider final :
		public BasePrimitiveCollider
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="direction"> : 向き</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint,
			const Vector3& direction,
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="direction"> : 向き</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const Vector3& direction,
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
		/// 初期位置
		/// </summary>
		/// <returns>初期位置</returns>
		Vector3 Start() const;

		/// <summary>
		/// 方向
		/// </summary>
		/// <returns>方向</returns>
		inline Vector3 Direction() const { return direction_.Normalized(); }

	public:

		RayCollider() = delete;

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="direction"> : 向き</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		RayCollider(
			Vector3* pFollowPoint,
			const Vector3& direction,
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="direction"> : 向き</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		RayCollider(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const Vector3& direction,
			const Vector3& offset = {},
			const bool isPushBack = false,
			const bool isSlip = false);

		virtual ~RayCollider() = default;

	protected:

		// 方向
		Vector3 direction_ = { 1,0,0 };

	protected:

		// 線 × 平面
		bool CheckConcreteCollision(const PlaneCollider& other) const override;

		// 線 × 三角形
		bool CheckConcreteCollision(const TriangleCollider& other) const override;

		// 線 × 球
		bool CheckConcreteCollision(const SphereCollider& other) const override;

	};
}