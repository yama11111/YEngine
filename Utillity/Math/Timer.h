#pragma once
#include "WorldRuler.h"

namespace YMath
{
	class Timer : private YGame::WorldRuleAdopter
	{
	private:
		// カウンタ
		float count_ = 0;
		// タイマー終了時刻
		float end_ = 0;
		// 動作しているか
		bool isAct_ = false;
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="end"> : 時間 (終了時のフレーム)</param>
		/// <param name="isApply"> : 世界のスピードが適用されるか</param>
		void Initialize(const unsigned int end, const bool isApply = true);
		/// <summary>
		/// リセット (中身だけ初期化)
		/// </summary>
		/// <param name="isAct"> : 初期化後すぐ動かすか</param>
		void Reset(const bool isAct);
		// 更新
		void Update();
	public:
		// 比率
		float Ratio();
		// 現在時刻
		float Current() { return count_; }
		// 動いているか
		bool IsAct() { return isAct_; }
		// 終了したか
		bool IsEnd() { return end_ != 0 && count_ == end_; }
		// 動作設定
		void SetActive(bool isAct) { isAct_ = isAct; }
	};
}