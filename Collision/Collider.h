#pragma once
#include "Vec3.h"
#include <cstdint>

namespace Collision
{
	class Collider
	{
	private:
		// 半径
		float radius_ = 0.0f;
		// 属性 (自分)
		uint32_t attribute_ = 0xffffffff;
		// マスク (相手)
		uint32_t mask_ = 0xffffffff;
		// すりぬけフラグ
		bool isSlip_ = false;
	public:
		struct InitStatus 
		{
			float radius_; // 半径
			uint32_t attribute_; // 属性 (自分)
			uint32_t mask_; // マスク (相手)
			bool isSlip_ = false; // すりぬけフラグ
		};
	public:
		// 衝突設定初期化
		void InitializeCollisionStatus(const InitStatus& state);
		// 衝突時処理
		virtual void OnCollision(const uint32_t attribute) = 0;
	public:
		// 位置取得
		virtual Math::Vec3 Pos() const = 0;
		// 半径取得
		float Radius() { return radius_; }
		// 半径設定
		void SetRadius(const float radius) { radius_ = radius; }
	public:
		// 属性取得
		uint32_t Attribute() const { return attribute_; }
		// 属性設定
		void SetAttribute(const uint32_t attribute) { attribute_ = attribute; }
		// マスク取得
		uint32_t Mask() const { return mask_; }
		// マスク設定
		void SetMask(const uint32_t mask) { mask_ = mask; }
		// すりぬけ取得
		bool IsSlip() const { return isSlip_; }
		// すりぬけ設定
		void SetIsSlip(const bool isSlip) { isSlip_ = isSlip; }
	};
}
