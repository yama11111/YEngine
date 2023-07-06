#include "Power.h"
#include <cmath>

using YMath::Power;

Power::Power(const uint32_t maxPower) : 
	current_(0),
	maxPower_(static_cast<float>(maxPower))
{	
}

void Power::Initialize(const uint32_t maxPower)
{
	// 代入
	SetMaxPower(maxPower);

	// リセット
	Reset();
}

void Power::Reset()
{
	// 初期化
	current_ = 0;
}

void Power::Update(const bool isAct)
{
	// 加算値
	float spd = 1.0f;

	// 動作中なら
	if (isAct)
	{
		// 加算 (最大値を超えないように)
		current_ = fminf(current_ + spd, maxPower_);
	}
	else
	{
		// 減算 (0.0fを超えないように)
		current_ = fmaxf(current_ - spd, 0.0f);
	}
}

float Power::Ratio()
{
	// 0で割らないように
	if (maxPower_ == 0) { return 0.0f; }
	return current_ / maxPower_;
}

void Power::SetMaxPower(const uint32_t maxPower)
{
	maxPower_ = static_cast<float>(maxPower);
}
