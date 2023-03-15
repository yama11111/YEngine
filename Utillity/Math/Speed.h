#pragma once
#include "Vector3.h"
#include "WorldRuler.h"

namespace YMath
{
	class Speed : public YGame::WorldRuleAdopter
	{
	private:
		// 加速度
		Vector3 acceleration_;
		// 最高速度
		Vector3 max_;
		// 実値
		Vector3 value_;

		bool isGravity_ = false;
	public:
		// 初期化
		void Initialize(const Vector3& acceleration, const Vector3& max, const bool isGravity = true);
		// リセット
		void Reset();
		// 更新
		void Update(const Vector3& power);
	private:
		// 計算
		static void Calculate(float& value, const float power, const float acceleration, const float max, const float dekey);
		// 計算 (重力)
		static void Gravity(float& value, const float power, const float acceleration, const float max, const float dekey);
	public:
		// 実値取得
		Vector3 Value() const { return value_; }
		// 最高速度
		Vector3 Max() const { return max_; }
		// 実値取得 (参照渡し)
		Vector3& ValueRef() { return value_; }
		// 向き取得
		Vector3 Direction() const { return value_.Normalized(); }
	};
}
