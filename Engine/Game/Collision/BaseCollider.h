#pragma once
#include "CollisionPrimitive.h"
#include <cstdint>

namespace YGame
{

	// コライダー基底クラス
	class BaseCollider : 
		public Sphere
	{
	
	public:

		/// <summary>
		/// 属性取得
		/// </summary>
		/// <returns>属性</returns>
		inline uint32_t Attribute() const { return attribute_; }

		/// <summary>
		/// マスク取得
		/// </summary>
		/// <returns>マスク</returns>
		inline uint32_t Mask() const { return mask_; }

		/// <summary>
		/// すり抜けフラグ取得
		/// </summary>
		/// <returns>すり抜けフラグ</returns>
		inline bool IsSlip() const { return isSlip_; };
	
	protected:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="attribute"> : 属性</param>
		/// <param name="mask"> : マスク</param>
		/// <param name="pPos"> : 位置ポインタ</param>
		/// <param name="radius"> : 半径</param>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		void Initialize(
			const uint32_t attribute, 
			const uint32_t mask, 
			YMath::Vector3* pPos,
			const float radius,
			const bool isSlip = false);
		
		/// <summary>
		/// 更新
		/// </summary>
		void Update();

	protected:

		/// <summary>
		/// 属性設定
		/// </summary>
		/// <param name="attribute"> : 属性</param>
		inline void SetAttribute(const uint32_t attribute) { attribute_ = attribute; }

		/// <summary>
		/// マスク設定
		/// </summary>
		/// <param name="mask"> : マスク</param>
		inline void SetMask(const uint32_t mask) { mask_ = mask; }

		/// <summary>
		/// すり抜けフラグ設定
		/// </summary>
		/// <param name="isSlip"> : すり抜けフラグ</param>
		inline void SetIsSlip(const bool isSlip) { isSlip_ = isSlip; }

		/// <summary>
		/// 位置ポインタ設定
		/// </summary>
		/// <param name="pPos"> : 位置ポインタ</param>
		void SetPosPointer(YMath::Vector3* pPos);

	public:

		BaseCollider() = default;

		virtual ~BaseCollider() = default;
	
	protected:
		
		// 属性 (自分)
		uint32_t attribute_ = 0xffffffff;
		
		// マスク (相手)
		uint32_t mask_ = 0xffffffff;

		// 位置ポインタ
		YMath::Vector3* pPos_ = nullptr;
		
		// すり抜けフラグ
		bool isSlip_ = false;

	};
}
