#include "Timer.h"
#include <cmath>

using YMath::Timer;

Timer::Timer(const uint32_t endFrame, const bool isAct) :
	current_(0),
	endFrame_(static_cast<float>(endFrame)),
	isAct_(isAct)
{
}

void Timer::Initialize(const uint32_t endFrame, const bool isAct)
{
	// 代入
	SetEndFrame(endFrame);

	// リセット
	Reset(false);
}

void Timer::Reset(const bool isAct)
{
	// 初期化
	current_ = 0;
	isAct_ = isAct;
}

void Timer::Update()
{
	// 動作中のみ通る
	if (isAct_ == false) { return; }

	// 加算値 (適用するなら時間スピード乗算)
	float spd = 1.0f;

	// 加算
	current_ += spd;
	
	// 時間になったら
	if (current_ >= endFrame_)
	{
		// 終了処理
		current_ = endFrame_;
		isAct_ = false;
	}
}

float Timer::Ratio()
{
	// 0で割らないように
	if (endFrame_ == 0) { return 0.0f; }
	return current_ / endFrame_;
}

void Timer::SetEndFrame(const uint32_t endFrame)
{
	// キャストして代入
	endFrame_ = static_cast<float>(endFrame);
}