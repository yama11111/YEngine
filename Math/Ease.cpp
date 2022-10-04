#include "Ease.h"
#include "Calc.h"
#include <cmath>

using Math::Ease;
using Math::Ease2;
using Math::Ease3;

float Math::EaseIn(const float start, const float end, const float time, const float power)
{
	return Lerp(start, end, pow(time, power));
}
float Math::EaseOut(const float start, const float end, const float time, const float power)
{
	return Lerp(start, end, 1 - pow(1 - time, power));
}

Ease::Ease() :
	ratio(0.0f), increase(0.0f)
{}

Ease::Ease(const float increase) :
	ratio(0.0f), increase(increase)
{}

void Ease::Initialize(const float increase)
{
	this->ratio = 0.0f;
	this->increase = increase;
}

void Ease::Update(const bool isEase)
{
	if (isEase)
	{
		ratio += increase;
		if (ratio >= 1.0f) ratio = 1.0f;
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
	decrease(0)
{}

Ease2::Ease2(const float increase, const float decrease)
{
	this->ratio = 0.0f;
	this->increase = increase;
	this->decrease = decrease;
}

void Ease2::Initialize(const float increase, const float decrease)
{
	this->ratio = 0.0f;
	this->increase = increase;
	this->decrease = decrease;
}

void Ease2::Update(const bool isEase)
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

Ease3::Ease3() :
	back(0.0f), pass(1.0f), extra(Extra::None)
{}

Ease3::Ease3(const float increase, const float decrease, const float value, const Extra extra) :
	extra(extra)
{
	this->ratio = 0.0f;
	this->increase = increase;
	this->decrease = decrease;

	switch (extra)
	{
	case Extra::Back:
		back = -value;
			break;
	case Extra::Pass:
		pass = 1.0f + value;
		break;
	case Extra::None:
		back = 0.0f;
		pass = 1.0f;
	default:
		break;
	}
}

void Ease3::Initialize(const float increase, const float decrease, const float value, const Extra extra)
{
	this->ratio = 0.0f;
	this->increase = increase;
	this->decrease = decrease;

	this->back = back;
	this->extra = extra;
}

void Ease3::Update(const bool isEase)
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