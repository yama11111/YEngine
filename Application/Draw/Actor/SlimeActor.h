#pragma once
#include "SplineEase.h"
#include "Timer.h"
#include "Power.h"
#include "Vector3.h"
#include <vector>

namespace YGame
{
	class SlimeActor
	{
	
	public:

		enum class EaseType
		{
			eIn,

			eOut,
		};
	
	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="wobbleScaleValues"> : 拡縮値ベクター配列</param>
		/// <param name="frame"> : フレーム</param>
		/// <param name="exponent"> : 指数</param>
		void Initialize(
			const uint32_t frame, 
			const std::vector<YMath::Vector3>& wobbleScaleValues, 
			const float exponent);

		/// <summary>
		/// ブヨブヨアニメーション
		/// </summary>
		void Wobble();
		
		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="isSquash"> : つぶす</param>
		void Update(const bool isSquash = false);
	
	public:
	
		/// <summary>
		/// 動作中か
		/// </summary>
		/// <returns>動作フラグ</returns>
		inline bool IsAct() const { return isAct_; }

		/// <summary>
		/// 現在の拡縮値取得
		/// </summary>
		/// <returns>現在の拡縮値</returns>
		YMath::Vector3 WobbleScaleValue(const EaseType easeType) const;
	
	public:
		
		virtual ~SlimeActor() = default;
	
	private:
		
		// 動作フラグ
		bool isAct_ = false;
		
		// イージング
		YMath::SplineEase<YMath::Vector3> ease_;
		
		// タイマー
		YMath::Timer timer_;
		
		// パワー
		YMath::Power power_;
	};
}

