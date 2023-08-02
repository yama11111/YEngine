#pragma once
#include "Vector3.h"

namespace YMath
{
	// スピード
	class Speed
	{
	
	public:
		
		/// <summary>
		/// </summary>
		/// 初期化
		/// <param name="acceleration"> : 加速度</param>
		/// <param name="max"> : 最大速度</param>
		/// <param name="isGravity"> : 重力フラグ</param>
		void Initialize(const Vector3& acceleration, const Vector3& max, const bool isGravity = true);

		/// <summary>
		/// リセット
		/// </summary>
		void Reset();

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="power"> : 力ベクトル</param>
		void Update(const Vector3& power);
	
	public:
		
		// 速度取得
		Vector3 Velocity() const { return velocity_; }
		
		// 最高速度
		Vector3 Max() const { return max_; }
		
		// 速度取得 (参照渡し)
		Vector3& VelocityRef() { return velocity_; }
		
		// 向き取得
		Vector3 Direction() const { return velocity_.Normalized(); }
	
	public:

		inline void SetAcceleration(const Vector3& acceleration) { acceleration_ = acceleration; }
		
		inline void SetMax(const Vector3& max) { max_ = max; }

		inline void SetIsGravity(const bool isGravity) { isGravity_ = isGravity; }
	
	private:
		
		// 加速度
		Vector3 acceleration_;
		
		// 最高速度
		Vector3 max_;
		
		// 速度
		Vector3 velocity_;


		// 重力フラグ
		bool isGravity_ = false;
	
	};
}
