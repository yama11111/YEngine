#include "Ease.h"
#include "Calc.h"

Ease::Ease() :
	ratio(0.0f), increase(0.0f), decrease(0.0f)
{
}

Ease::Ease(float increase, float decrease) :
	ratio(0.0f), increase(increase), decrease(decrease)
{
}

void Ease::Initialize(float increase, float decrease)
{
	this->ratio = 0.0f;
	this->increase = increase;
	this->decrease = decrease;
}

void Ease::Update(const bool isIncrease)
{
	if (isIncrease)
	{
		ratio += increase;
		if (ratio >= 1.0f) ratio = 1.0f;
	}
	else
	{
		ratio -= decrease;
		if (ratio <= 0.0f) ratio = 0.0f;
	}
}

float Ease::In(const float start, const float end, const float power)
{
	return EaseIn(start, end, ratio, power);
}

float Ease::Out(const float start, const float end, const float power)
{
	return EaseOut(start, end, ratio, power);
}
