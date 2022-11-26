#pragma once
#include "Vec3.h"
#include "CollisionConfig.h"

namespace Collision
{
	class Collider
	{
	private:
		// 半径
		float radius_ = 0.0f;
		// 属性 (自分自身)
		uint32_t attribute_ = 0xffffffff;
		// マスク (何と当たるか)
		uint32_t mask_ = 0xffffffff;
		// すりぬけフラグ
		bool isSlip_ = false;
	public:
		// 衝突時処理
		virtual void OnCollision(const uint32_t attribute) = 0;
	public:
		// 位置取得
		virtual Math::Vec3 GetWorldPos() = 0;
		// 半径取得
		float Radius() { return radius_; }
		// 半径設定
		void SetRadius(const float radius) { radius_ = radius; }
	public:
		// 属性取得
		uint32_t Attribute() { return attribute_; }
		// 属性設定
		void SetAttribute(const uint32_t attribute) { attribute_ = attribute; }
		// マスク取得
		uint32_t Mask() { return mask_; }
		// マスク設定
		void SetMask(const uint32_t mask) { mask_ = mask; }
		// すりぬけ取得
		bool IsSlip() { return isSlip_; }
		// すりぬけ設定
		void SetIsSlip(const bool isSlip) { isSlip_ = isSlip; }
	};
}
