#pragma once
#include "Transform.h"
#include "Timer.h"
#include <unordered_map>

namespace YGame
{
	// アニメーションクラス
	class Animation
	{
	
	public:

		/// <summary>
		/// クリア
		/// </summary>
		void Clear();
		
		/// <summary>
		/// アニメーションタイマー挿入
		/// </summary>
		/// <param name="index"> : 番号</param>
		/// <param name="endFrame"> : 終了時の時間 (F)</param>
		/// <param name="isRoop"> : ループするか</param>		
		void InsertAnimationTimer(const uint32_t index, const uint32_t endFrame, const bool isRoop);
		
		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="status"> : ステータス</param>
		//void Update(const Transform::Status& status);
		void Update();

		/// <summary>
		/// タイマーリセット
		/// </summary>
		/// <param name="index"> : 番号</param>
		void ResetTimer(const uint32_t index, const uint32_t endFrame, const bool isRoop);

		/// <summary>
		/// タイマー開始
		/// </summary>
		/// <param name="index"> : 番号</param>
		void StartTimer(const uint32_t index);

		/// <summary>
		/// タイマー停止
		/// </summary>
		/// <param name="index"> : 番号</param>
		void StopTimer(const uint32_t index);

	public:
		
		/// <summary>
		/// タイマー比率取得
		/// </summary>
		/// <param name="index"> : 番号</param>
		/// <returns>タイマー比率</returns>
		float TimerRatio(const uint32_t index);
	
	private:

		// アニメーション用タイマー
		struct AnimationTimer
		{
			// タイマー
			YMath::Timer timer;

			// ループするか
			bool isRoop = false;
		};
	
	private:

		// アニメーションビットフラグ
		uint32_t animationBitFlag_ = 0;

		// アニメーションタイマーマップ
		std::unordered_map<uint32_t, AnimationTimer> animationTimers_;
	
	private:

		// タイマー更新
		void UpdateTimer();

	};
}
