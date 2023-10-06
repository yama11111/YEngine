#pragma once
#include <cstdint>

namespace YMath
{
	class Power
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="maxPower"> : 最大パワー</param>
		void Initialize(const uint32_t maxPower);

		/// <summary>
		/// リセット (中身だけ初期化)
		/// </summary>
		void Reset();

		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="isAct"> : 動作するか (動作中加算)</param>
		void Update(const bool isAct);

	public:

		/// <summary>
		/// 比率
		/// </summary>
		float Ratio() const;

		/// <summary>
		/// 現在パワー
		/// </summary>
		inline float Current() const { return current_; }

		/// <summary>
		/// 最大パワー
		/// </summary>
		inline float Max() const { return maxPower_; }

		/// <summary>
		/// 最大か
		/// </summary>
		inline bool IsMax() const { return current_ == maxPower_; }

		/// <summary>
		/// ゼロか
		/// </summary>
		inline bool IsZero() const { return current_ == 0; }

	public:

		/// <summary>
		/// 最終値設定
		/// </summary>
		/// <param name="max"></param>
		void SetMaxPower(const uint32_t max);

	public:

		Power() = default;

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="maxPower"> : 最大パワー</param>
		Power(const uint32_t maxPower);
		
		~Power() = default;
	
	private:
		
		// 現在パワー
		float current_ = 0;
		
		// 最大時パワー
		float maxPower_ = 0;
	};
}