#pragma once
#include <functional>

class TimedCall 
{
private:
	std::function<void(void)> call;
	uint32_t time;
	bool isFinished = false;

public:
	TimedCall(std::function<void(void)> call, uint32_t time);
	void Update();
	bool IsFinished() { return isFinished; }
};
