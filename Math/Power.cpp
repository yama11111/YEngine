#include "Power.h"

using Math::Power;

void Power::Initialize(const unsigned int max)
{
	p_ = max;
	Reset();
}

void Power::Reset()
{
	count_ = 0;
	isAct_ = false;
}

void Power::Update(const bool isAct)
{
	isAct_ = isAct;
	if (isAct)
	{
		if (++count_ >= p_) { count_ = p_; }
	}
	else
	{
		if (--count_ <= 0) { count_ = 0; }
	}
}

float Power::Ratio()
{
	if (p_ == 0) { return 0.0f; }
	return static_cast<float>(count_) / static_cast<float>(p_);
}