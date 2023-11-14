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

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="other"> : 相手</param>
		/// <returns>衝突したか</returns>
		virtual bool CheckCollision(const BasePrimitiveCollider& other) = 0;

	public:

		// 具体的な処理
		virtual bool CheckConcreteCollision(const RayCollider& other) const;
		virtual bool CheckConcreteCollision(const PlaneCollider& other) const;
		virtual bool CheckConcreteCollision(const TriangleCollider& other) const;
		virtual bool CheckConcreteCollision(const SphereCollider& other) const;
		virtual bool CheckConcreteCollision(const Box2DCollider& other) const;
		virtual bool CheckConcreteCollisionAndPushBack(Box2DCollider& other) const;

	public:

		/// <summary>
		/// 追従点設定
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		void SetFollowPoint(YMath::Vector3* pFollowPoint) { pFollowPoint_ = pFollowPoint; }

		/// <summary>
		/// 進行方向設定
		/// </summary>
		/// <param name="pVelocity"> : 進行方向</param>
		void SetVelocity(YMath::Vector3* pVelocity) { pVelocity_ = pVelocity; }

		/// <summary>
		// ずれ設定
		/// </summary>
		/// <param name="offset"> : ずれ</param>
		void SetOffset(const Vector3& offset) { offset_ = offset; }

		/// <summary>
		/// 押し戻しフラグ設定
		/// </summary>
		/// <returns>押し戻しフラグ</returns>
		void SetIsPushBack(const bool isPushBack) { isPushBack_ = isPushBack; }

		/// <summary>
		/// すり抜けフラグ設定
		/// </summary>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void SetIsSlip(const bool isSlip) { isSlip_ = isSlip; }

	public:

		/// <summary>
		/// 追従点取得
		/// </summary>
		/// <returns>追従点</returns>
		Vector3 FollowPoint() const { return *pFollowPoint_; }

		/// <summary>
		/// 追従点ポインタ取得
		/// </summary>
		/// <returns>追従点ポインタ</returns>
		Vector3* FollowPointPtr() { return pFollowPoint_; }

		/// <summary>
		/// 速度取得
		/// </summary>
		/// <returns>速度</returns>
		Vector3 Velocity() const;

		/// <summary>
		/// 速度ポインタ取得
		/// </summary>
		/// <returns>速度ポインタ</returns>
		Vector3* VelocityPtr() { return pVelocity_; }

		/// <summary>
		/// 押し戻しフラグ取得
		/// </summary>
		/// <returns>押し戻しフラグ</returns>
		inline bool IsPushBack() const { return isPushBack_; }

		/// <summary>
		/// すり抜けフラグ取得
		/// </summary>
		/// <returns>すり抜けフラグ</returns>
		bool IsSlip() const { return isSlip_; }
	
	public:
		
		BasePrimitiveCollider() = default;

		virtual ~BasePrimitiveCollider() = default;

	protected:

		// 追従点
		Vector3* pFollowPoint_ = nullptr;

		// 進行方向
		Vector3* pVelocity_ = nullptr;

		// オフセット
		Vector3 offset_;

		// 押し戻しフラグ
		bool isPushBack_ = false;

		// すり抜けフラグ
		bool isSlip_ = false;

	protected:

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		BasePrimitiveCollider(
			Vector3* pFollowPoint,
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 進行方向</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		BasePrimitiveCollider(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const Vector3& offset = {},
			const bool isPushBack = false,
			const bool isSlip = false);

	protected:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint,
			const Vector3& offset = {},
			const bool isSlip = false);

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pFollowPoint"> : 追従点</param>
		/// <param name="pVelocity"> : 進行方向</param>
		/// <param name="offset"> : オフセット</param>
		/// <param name="isPushBack"> : 押し戻しフラグ</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			Vector3* pFollowPoint,
			Vector3* pVelocity,
			const Vector3& offset = {},
			const bool isPushBack = false,
			const bool isSlip = false);
	};
}

