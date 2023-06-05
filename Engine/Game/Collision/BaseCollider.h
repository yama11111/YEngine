#pragma once
#include "Vector3.h"
#include <cstdint>

namespace YGame
{

	// コライダー基底クラス
	class BaseCollider
	{

	public:

		// 衝突型
		enum class ShapeType
		{
			eUnkown = -1, // 未設定

			eSphere, // 球
		};
	
	protected:
		
		// オフセット
		YMath::Vector3 offset_;
		
		// 衝突型
		ShapeType shape_ = ShapeType::eUnkown;
		
		// 属性 (自分)
		uint32_t attribute_ = 0xffffffff;
		
		// マスク (相手)
		uint32_t mask_ = 0xffffffff;
		
		// すり抜けフラグ
		bool isSlip_ = false;
	
	public:
		
		// 衝突情報
		struct CollsionInfo
		{
		
		public:
			BaseCollider* pair_ = nullptr; // コライダー (相手)
			//YMath::Vector3 inter; // 衝突点
		};
	
	public:
		
		// 更新
		virtual void Update() = 0;
		
		// 衝突時コールバック関数
		virtual void OnCollision(const CollsionInfo& info) = 0;
	
	public:
		// オフセット値取得
		inline virtual YMath::Vector3 GetPos() const;
		// オフセット値取得
		inline YMath::Vector3 SetOffset() const { return offset_; }
		// オフセット値設定
		inline void SetOffset(const YMath::Vector3& offset) { offset_ = offset; }
		// 衝突型取得
		inline ShapeType GetShapeType() const { return shape_; }
		// 属性取得
		inline uint32_t GetAttribute() const { return attribute_; }
		// 属性設定
		inline void SetAttribute(const uint32_t attribute) { attribute_ = attribute; }
		// マスク取得
		inline uint32_t GetMask() const { return mask_; }
		// マスク設定
		inline void SetMask(const uint32_t mask) { mask_ = mask; }
		// すり抜けフラグ取得
		inline bool GetIsSlip() const { return isSlip_; }
		// すり抜けフラグ設定
		inline void SetIsSlip(const bool isSlip) { isSlip_ = isSlip; }
	public:
		BaseCollider() = default;
		virtual ~BaseCollider() = default;
	};
}
