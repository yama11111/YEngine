//#pragma once
//#include "BaseCollider.h"
//#include "CollisionPrimitive.h"
//
//namespace YGame
//{
//	class SphereCollider :
//		public BaseCollider,
//		private Sphere
//	{
//	public:
//		/// <summary>
//		/// 初期化
//		/// </summary>
//		/// <param name="center">/ 中心座標</param>
//		/// <param name="radius">/ 半径</param>
//		/// <param name="offset">/ オフセット</param>
//		/// <param name="attribute">/ 属性(自分)</param>
//		/// <param name="mask">/ マスク(相手)</param>
//		/// <param name="isInvincible">/ 無敵フラグ</param>
//		void Initialize(
//			const YMath::Vector3& center,
//			const float radius,
//			YMath::Vector3 offset = { 0.0f,0.0f,0.0f },
//			uint32_t attribute = 0xffffffff,
//			uint32_t mask = 0xffffffff,
//			bool isInvincible = false);
//		// 衝突時コールバック関数
//		virtual void OnCollision(const CollsionInfo& info) = 0;
//	public:
//		// 位置取得
//		inline YMath::Vector3 GetPos() const override { return center_ + offset_; }
//		// 中心座標取得
//		inline YMath::Vector3 GetCenter() const { return center_; }
//		// 中心座標設定
//		inline void SetCenter(const YMath::Vector3& center) { center_ = center; }
//		// 半径取得
//		inline float GetRadius() const { return radius_; }
//		// 半径設定
//		inline void SetRadius(const float radius) { SafeSetRadius(radius); }
//	};
//}
//
