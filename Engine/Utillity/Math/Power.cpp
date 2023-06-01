#include "Power.h"
#include <cmath>

using YMath::Power;

void Power::Initialize(const unsigned int max, const bool isApply)
{
	// 代入
	max_ = static_cast<float>(max);
	isApply_ = isApply;

	// リセット
	Reset();
}

void Power::Reset()
{
	// 初期化
	count_ = 0;
}

void Power::Update(const bool isAct)
{
	// 加算値 (適用するなら時間スピード乗算)
	float spd = 1.0f;
	if (isApply_) { spd *= spWorldRuler_->GetTimeSpeed(); }

	// 動作中なら
	if (isAct)
	{
		// 加算 (最大値を超えないように)
		count_ = fminf(count_ + spd, max_);
	}
	else
	{
		// 減算 (0.0fを超えないように)
		count_ = fmaxf(count_ - spd, 0.0f);
	}
}

float Power::Ratio()
{
	// 0で割らないように
	if (max_ == 0) { return 0.0f; }
	return count_ / max_;
}