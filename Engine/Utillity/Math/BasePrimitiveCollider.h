#pragma once
#include "Vector3.h"

namespace YMath
{
	// ダブルディスパッチ用
	class RayCollider;
	class PlaneCollider;
	class TriangleCollider;
	class SphereCollider;
	class Box2DCollider;

	// プリミティブコライダー基底クラス
	class BasePrimitiveCollider
	{

	public:

		// すり抜けフラグ
		bool isSlip_ = false;

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="offset"> : ずれ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(Vector3* pFollowPoint, const Vector3& offset, const bool isSlip = false);

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="other"> : 相手</param>
		/// <returns>衝突したか</returns>
		virtual bool CheckCollision(const BasePrimitiveCollider& other) const = 0;

	public:

		/// <summary>
		// 追従点設定
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		inline void SetFollowPoint(Vector3* pFollowPoint) { pFollowPoint_ = pFollowPoint; }

		/// <summary>
		// ずれ設定
		/// </summary>
		/// <param name="offset"> : ずれ</param>
		inline void SetOffset(const Vector3& offset) { offset_ = offset; }
	
	public:

		// 具体的な処理
		virtual bool CheckConcreteCollision(const RayCollider& other) const { return false; }
		virtual bool CheckConcreteCollision(const PlaneCollider& other) const { return false; }
		virtual bool CheckConcreteCollision(const TriangleCollider& other) const { return false; }
		virtual bool CheckConcreteCollision(const SphereCollider& other) const { return false; }
		virtual bool CheckConcreteCollision(const Box2DCollider& other) const { return false; }

	protected:

		// 追従点
		Vector3* pFollowPoint_ = nullptr;

		// ずれ
		Vector3 offset_;

	public:

		BasePrimitiveCollider() = default;

		BasePrimitiveCollider(const bool isSlip);
		
		BasePrimitiveCollider(Vector3* pFollowPoint, const Vector3& offset, const bool isSlip = false);

		virtual ~BasePrimitiveCollider() = default;
	};
}

