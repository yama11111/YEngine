#include "Timer.h"

using YMath::Timer;

void Timer::Initialize(const unsigned int end, const bool isApply)
{
	// 代入
	end_ = static_cast<float>(end);
	isApply_ = isApply;

	// リセット
	Reset(false);
}

void Timer::Reset(const bool isAct)
{
	// 初期化
	count_ = 0;
	isAct_ = isAct;
}

void Timer::Update()
{
	// 動作中のみ通る
	if (isAct_ == false) { return; }

	// 加算値 (適用するなら時間スピード乗算)
	float spd = 1.0f;
	if (isApply_) { spd *= spWorldRuler_->GetTimeSpeed(); }

	// 加算
	count_ += spd;
	
	// 時間になったら
	if (count_ >= end_)
	{
		// 終了処理
		count_ = end_;
		isAct_ = false;
	}
}

float Timer::Ratio()
{
	// 0で割らないように
	if (end_ == 0) { return 0.0f; }
	return count_ / end_;
}
