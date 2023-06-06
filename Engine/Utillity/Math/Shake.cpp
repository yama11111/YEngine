#include "Shake.h"
#include "MathUtil.h"

using YMath::Shake;

void Shake::Initialize()
{
	// ‰Šú‰»
	isAct_ = false;
	swing_ = 0.0f;
	dekey_ = 0.0f;
	place_ = 0.0f;
	value_ = {};
}

void Shake::Activate(const float swing, const float dekey, const float place)
{
	// “®ì‚µ‚Ä‚¢‚È‚¢‚È‚ç
	if (!isAct_)
	{
		// ‰Šú‰» + ‘ã“ü
		dekey_ = dekey;
		swing_ = swing;
		place_ = place;
		value_ = {};

		// “®ìŠJn
		isAct_ = true;
	}
	// —h‚ê—Ê‚ª¡‚æ‚è‘å‚«‚¢‚È‚ç
	else if (swing_ <= swing)
	{
		// ‘ã“ü
		dekey_ = dekey;
		swing_ = swing;
		place_ = place;
	}
}

void Shake::Update()
{
	// ”ÍˆÍ‚ª0ˆÈã‚È‚ç
	if (swing_ > 0) 
	{
		// ”ÍˆÍ‚ğ‹·‚ß‚é
		swing_ -= dekey_; 
	}
	// ‚»‚êˆÈŠO‚È‚ç
	else
	{
		// ‰Šú‰»
		Initialize();
	}

	// “®ì’†‚È‚ç
	if (isAct_)
	{
		// ”ÍˆÍ“à‚Ì—”¶¬
		value_.x_ = GetRand(-swing_, swing_, place_);
		value_.y_ = GetRand(-swing_, swing_, place_);
		value_.z_ = GetRand(-swing_, swing_, place_);
	}
}
