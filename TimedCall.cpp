#include "TimedCall.h"

TimedCall::TimedCall(std::function<void(void)> call, uint32_t time) :
	call(call), time(time) {}

void TimedCall::Update() 
{
	if (isFinished) return;
	time--;
	if (time <= 0) 
	{
		isFinished = true;
		call();
	}
}
