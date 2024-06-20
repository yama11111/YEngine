#include "Timer.h"
#include <cmath>

using YMath::Timer;

Timer::Timer(const uint32_t endFrame, const bool isAct) :
	current_(0),
	endFrame_(endFrame),
	isAct_(isAct)
{
}

void Timer::Initialize(const uint32_t endFrame, const bool isAct)
{
	// 代入
	SetEndFrame(endFrame);

	// リセット
	Reset(isAct);
}

void Timer::Reset(const bool isAct)
{
	// 初期化
	current_ = 0;
	isAct_ = isAct;
}

void Timer::Update(const float passRate)
{
	// 動作中のみ通る
	if (isAct_ == false) { return; }

	// 加算値
	float spd = 1.0f * passRate;

	// 加算
	current_ += spd;
	
	// 時間になったら
	if (current_ >= static_cast<float>(endFrame_))
	{
		// 終了処理
		Finish();
	}
}

void Timer::Finish()
{
	current_ = static_cast<float>(endFrame_);
	isAct_ = false;
}

float Timer::Ratio() const
{
	// 0で割らないように
	if (endFrame_ == 0) { return 0.0f; }
	return current_ / static_cast<float>(endFrame_);
}

void Timer::SetActive(const bool isAct)
{
	if (IsEnd()) { return; }
	isAct_ = isAct;
}