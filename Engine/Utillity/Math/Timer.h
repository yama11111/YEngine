#pragma once
#include <cstdint>

namespace YMath
{
	class Timer
	{
	
	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="endFrame"> : 終了時の時間 (F)</param>
		/// <param name="isAct"> : 初期化後すぐ動かすか</param>
		void Initialize(const uint32_t endFrame, const bool isAct = false);
		
		/// <summary>
		/// リセット (中身だけ初期化)
		/// </summary>
		/// <param name="isAct"> : 初期化後すぐ動かすか</param>
		void Reset(const bool isAct);
		
		/// <summary>
		/// 更新
		/// </summary>
		void Update();
	
	public:
		
		/// <summary>
		/// 比率
		/// </summary>
		float Ratio();

		/// <summary>
		/// 現在時刻
		/// </summary>
		inline float Current() const { return current_; }

		/// <summary>
		/// 最終時間
		/// </summary>
		inline float EndFrame() const { return endFrame_; }

		/// <summary>
		/// 動いているか
		/// </summary>
		inline bool IsAct() const { return isAct_; }

		/// <summary>
		/// 終了したか
		/// </summary>
		inline bool IsEnd() const { return endFrame_ != 0 && current_ == endFrame_; }

	public:
		
		/// <summary>
		/// 動作設定
		/// </summary>
		/// <param name="isAct"> : 動かすか</param>
		inline void SetActive(const bool isAct) { isAct_ = isAct; }

		/// <summary>
		/// 終了時刻設定
		/// </summary>
		/// <param name="end"> : 終了時刻 (F)</param>
		void SetEndFrame(const uint32_t endFrame);

	public:

		Timer() = default;

		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="endFrame"> : 終了時の時間 (F)</param>
		/// <param name="isAct"> : 初期化後すぐ動かすか</param>
		Timer(const uint32_t endFrame, const bool isAct = false);
		
		~Timer() = default;

	private:

		// 動作しているか
		bool isAct_ = false;

		// 現在時間
		float current_ = 0;

		// タイマー終了時刻
		float endFrame_ = 0;
	};
}