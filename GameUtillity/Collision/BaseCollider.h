#pragma once
#include "Vector3.h"
#include <cstdint>

namespace YGame
{
	// 衝突型
	enum class ShapeType
	{
		ShapeUnkown = -1, // 未設定

		CollsionShapeSphere, // 球
	};

	// コライダー基底クラス
	class BaseCollider
	{
	protected:
		// オフセット
		YMath::Vector3 offset_;
		// 衝突型
		ShapeType shape_ = ShapeType::ShapeUnkown;
		// 属性 (自分)
		uint32_t attribute_ = 0xffffffff;
		// マスク (相手)
		uint32_t mask_ = 0xffffffff;
		// 無敵フラグ
		bool isInvincible_ = false;
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
		// 無敵フラグ取得
		inline bool GetIsInvincible() const { return isInvincible_; }
		// 無敵フラグ設定
		inline void SetIsInvincible(const bool isInvincible) { isInvincible_ = isInvincible; }
	public:
		BaseCollider() = default;
		~BaseCollider() = default;
	};
}
