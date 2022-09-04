#pragma once

namespace Math
{
	class Timer
	{
	public:
		float timer;
		float maxTime;
		float increase;
		bool isEnd;
	public:
		Timer();
		Timer(const float maxTime, const float increase);
		void Initialize(const float maxTime, const float increase);
		void Update();
		void Reset();
		bool IsEnd() { return isEnd; }
	};
}
