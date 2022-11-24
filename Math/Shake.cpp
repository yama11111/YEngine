#include "Shake.h"
#include "YMath.h"

using Math::Shake;

void Shake::Initialize()
{
	value_ = { 0,0,0 };
	isAct_ = false;
	swing_ = 0;
	dekey_ = 0;
}

void Shake::Activate(const int swing, const int dekey)
{
	if (!isAct_)
	{
		value_ = { 0,0,0 };
		isAct_ = true;
		dekey_ = dekey;
		swing_ = swing;
	}
	else if (swing_ <= swing)
	{
		dekey_ = dekey;
		swing_ = swing;
	}
}

void Shake::Update()
{
	// ”ÍˆÍ‚ğ‹·‚ß‚é
	if (swing_ > 0) { swing_ -= dekey_; }

	// ”ÍˆÍ“à‚Ì—”¶¬
	if (isAct_)
	{
		value_.x_ = static_cast<float>(GetRand(-swing_, swing_));
		value_.y_ = static_cast<float>(GetRand(-swing_, swing_));
		value_.z_ = static_cast<float>(GetRand(-swing_, swing_));
	}

	if (swing_ <= 0)
	{
		value_ = { 0,0,0 };
		swing_ = 0;
		dekey_ = 0;
		isAct_ = false;
	}
}
