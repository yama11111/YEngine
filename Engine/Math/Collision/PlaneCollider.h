#pragma once
#include "Vector2.h"
#include "BasePrimitiveCollider.h"

namespace YMath
{
	// 平面
	class PlaneCollider final :
		public BasePrimitiveCollider
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="normal"> : 法線</param>
		/// <param name="distance"> : 距離</param>
		/// <param name="rectangle"> : 縦横サイズ</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint,
			const Vector3& normal,
			const float distance,
			const Vector2& rectangle,
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="normal"> : 法線</param>
		/// <param name="distance"> : 距離</param>
		/// <param name="rectangle"> : 縦横サイズ</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const Vector3& normal,
			const float distance,
			const Vector2& rectangle,
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
		/// 法線
		/// </summary>
		/// <returns>法線</returns>
		inline Vector3 Normal() const { return normal_.Normalized(); }

		/// <summary>
		/// 距離
		/// </summary>
		/// <returns>距離</returns>
		inline float Distance() const { return distance_; }

	public:

		PlaneCollider() = delete;

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="normal"> : 法線</param>
		/// <param name="distance"> : 距離</param>
		/// <param name="rectangle"> : 縦横サイズ</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		PlaneCollider(
			Vector3* pFollowPoint,
			const Vector3& normal,
			const float distance,
			const Vector2& rectangle,
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="normal"> : 法線</param>
		/// <param name="distance"> : 距離</param>
		/// <param name="rectangle"> : 縦横サイズ</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		PlaneCollider(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const Vector3& normal,
			const float distance,
			const Vector2& rectangle,
			const Vector3& offset = {},
			const bool isPushBack = false,
			const bool isSlip = false);


		virtual ~PlaneCollider() = default;

	protected:

		// 法線ベクトル
		Vector3 normal_ = { 0.0f,+1.0f,0.0f };

		// 原点からの距離
		float distance_ = 0.0f;

		// 縦横サイズ
		Vector2 rectangle_ = {};

	protected:

		// 線 × 平面
		bool CheckConcreteCollision(const RayCollider& other) const override;

		// 平面 × 球
		bool CheckConcreteCollision(const SphereCollider& other) const override;
	};
}
