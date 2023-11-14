#pragma once
#include "BasePrimitiveCollider.h"
#include <array>

namespace YMath
{
	// 三角形
	class TriangleCollider final :
		public BasePrimitiveCollider
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="vertices"> : 頂点位置</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint,
			const std::array<Vector3, 3>& vertices,
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="vertices"> : 頂点位置</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const std::array<Vector3, 3>& vertices,
			const Vector3& offset = {},
			const bool isPushBack = false,
			const bool isSlip = false);

		/// <summary>
		/// 三角形法線の計算 (現在の3点から)
		/// </summary>
		void CalcTriangleNormal();

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="other"> : 相手</param>
		/// <returns>衝突したか</returns>
		bool CheckCollision(const BasePrimitiveCollider& other) override;

	public:

		/// <summary>
		/// 三角形頂点位置
		/// </summary>
		/// <param name="index">インデックス</param>
		/// <returns>三角形頂点位置</returns>
		YMath::Vector3 VertexPos(const size_t index) const;

		/// <summary>
		/// 法線
		/// </summary>
		/// <returns>法線</returns>
		inline YMath::Vector3 Normal() const { return normal_; }

	public:

		TriangleCollider() = delete;

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="vertices"> : 頂点位置</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		TriangleCollider(
			Vector3* pFollowPoint,
			const std::array<Vector3, 3>& vertices,
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 速度ベクトル</param>
		/// <param name="vertices"> : 頂点位置</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		TriangleCollider(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const std::array<Vector3, 3>& vertices,
			const Vector3& offset = {},
			const bool isPushBack = false,
			const bool isSlip = false);

		virtual ~TriangleCollider() = default;

	protected:

		// 頂点座標
		std::array<Vector3, 3> vertices_;

		// 法線ベクトル
		Vector3 normal_;

	protected:

		// 線 × 三角形
		bool CheckConcreteCollision(const RayCollider& other) const override;

		// 三角形 × 球
		bool CheckConcreteCollision(const SphereCollider& other) const override;

	};
}

