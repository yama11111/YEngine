#pragma once
class Ease
{
public:
	float ratio;
	float increase;
	float decrease;
public:
	Ease();
	Ease(float increase, float decresae);
	void Initialize(float increase, float decresae);
	void Update(const bool isIncrease);
	float In(const float start, const float end, const float power);
	float Out(const float start, const float end, const float power);
};

