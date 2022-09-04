#include "Ease.h"
#include "Calc.h"

using Math::Ease;
using Math::Ease2;

Ease::Ease() :
	ratio(0.0f), increase(0.0f), decrease(0.0f)
{}

Ease::Ease(const float increase, const float decrease) :
	ratio(0.0f), increase(increase), decrease(decrease)
{}

void Ease::Initialize(const float increase, const float decrease)
{
	this->ratio = 0.0f;
	this->increase = increase;
	this->decrease = decrease;
}

void Ease::Update(const bool isEase)
{
	if (isEase)
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

Ease2::Ease2() :
	back(0.0f), pass(1.0f), extra(None)
{}

Ease2::Ease2(const float increase, const float decrease, const float value, const Extra extra) :
	extra(extra)
{
	this->ratio = 0.0f;
	this->increase = increase;
	this->decrease = decrease;

	switch (extra)
	{
	case Back:
		back = -value;
			break;
	case Pass:
		pass = 1.0f + value;
		break;
	case None:
		back = 0.0f;
		pass = 1.0f;
	default:
		break;
	}
}

void Ease2::Initialize(const float increase, const float decrease, const float value, const Extra extra)
{
	this->ratio = 0.0f;
	this->increase = increase;
	this->decrease = decrease;

	this->back = back;
	this->extra = extra;
}

void Ease2::Update(const bool isEase)
{
	//if (isEase)
	//{
	//	ratio += increase;
	//	if (ratio >= pass) ratio = pass;
	//}
	//else
	//{
	//	ratio -= decrease;
	//	if (ratio <= back) ratio = back;
	//}
}