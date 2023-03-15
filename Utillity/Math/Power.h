#pragma once
#include "WorldRuler.h"

namespace YMath
{
	class Power : private YGame::WorldRuleAdopter
	{
	private:
		// カウンタ
		float count_ = 0;
		// パワー最大時
		float max_ = 0;
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="max"> : 量 (最大時のパワー)</param>
		/// <param name="isApply"> : 世界のスピードが適用されるか</param>
		void Initialize(const unsigned int max, const bool isApply = true);
		// リセット
		void Reset();
		// 更新
		void Update(const bool isAct);
	public:
		// 比率
		float Ratio();
		// 現在パワー
		float Current() { return count_; }
		// 最大か
		bool IsMax() { return count_ == max_; }
		// ゼロか
		bool IsZero() { return count_ == 0; }
	};
}