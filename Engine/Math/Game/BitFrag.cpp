#include "BitFrag.h"

using YMath::BitFrag;

void BitFrag::Initialize()
{
	bit_ = 0;
}

void BitFrag::SetFragTrue(const BitFrag bitFrag)
{
	bit_ |= bitFrag.Bit();
}

void BitFrag::SetFragFalse(const BitFrag bitFrag)
{
	bit_ &= ~bitFrag.Bit();
}

bool BitFrag::OR(const BitFrag& other) const
{
	return bit_ | other.Bit();
}

bool BitFrag::AND(const BitFrag& other) const
{
	return bit_ & other.Bit();
}

uint32_t BitFrag::Bit() const
{
	return bit_;
}
