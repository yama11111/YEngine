#include "Timer.h"

using Math::Timer;

Timer::Timer() :
	timer(0.0f), maxTime(0.0f), increase(0.0f), isEnd(false)
{
}

Timer::Timer(const float maxTime, const float increase) :
	timer(0.0f), maxTime(maxTime), increase(increase), isEnd(false)
{
}

void Timer::Initialize(const float maxTime, const float increase)
{
	timer = 0.0f;
	this->maxTime = maxTime;
	this->increase = increase;
	isEnd = false;
}

void Timer::Reset()
{
	timer = 0.0f;
	isEnd = false;
}

void Timer::Update()
{
	timer += increase;
	if (maxTime <= timer)
	{
		timer = 0.0f;
		isEnd = true;
	}
	else isEnd = false;
}
