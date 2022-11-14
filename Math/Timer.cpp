#include "Timer.h"

using Math::Timer;

void Timer::Initialize(const unsigned int time)
{
	t_ = time;
	Reset(false);
}

void Timer::Reset(const bool isAct)
{
	count_ = 0;
	isAct_ = isAct;
}

void Timer::Update()
{
	if (!isAct_) { return; }

	if (++count_ >= t_)
	{
		count_ = t_;
		isAct_ = false;
	}
}

float Timer::Ratio()
{
	if (t_ == 0) { return 0.0f; }
	return static_cast<float>(count_) / static_cast<float>(t_);
}
