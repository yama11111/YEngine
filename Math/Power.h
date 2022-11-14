#pragma once

namespace Math
{
	class Power
	{
	private:
		// カウンタ
		int count_ = 0;
		// パワー最大時
		int p_ = 0;
		// 動作しているか
		bool isAct_ = false;
	public:
		// 初期化
		void Initialize(const unsigned int max);
		// リセット
		void Reset();
		// 更新
		void Update(const bool isAct);
	public:
		// 比率
		float Ratio();
		// 現在パワー
		unsigned int Current() { return count_; }
		// 動いているか
		bool IsAct() { return isAct_; }
		// 最大か
		bool IsMax() { return count_ == p_; }
		// ゼロか
		bool IsZero() { return count_ == 0; }
	};
}