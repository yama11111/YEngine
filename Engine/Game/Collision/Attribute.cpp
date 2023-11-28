#include "Attribute.h"

using YGame::Attribute;

void Attribute::Initialize()
{
	attributeBit_ = 0;
}

void Attribute::Add(const AttributeType attributeType)
{
	attributeBit_ |= static_cast<uint32_t>(attributeType);
}

void Attribute::Remove(const AttributeType attributeType)
{
	attributeBit_ &= ~static_cast<uint32_t>(attributeType);
}

bool Attribute::OR(const Attribute& other) const
{
	return attributeBit_ | other.Bit();
}
bool Attribute::OR(const AttributeType other) const
{
	return attributeBit_ | static_cast<uint32_t>(other);
}

bool Attribute::AND(const Attribute& other) const
{
	return attributeBit_ & other.Bit();
}
bool Attribute::AND(const AttributeType other) const
{
	return attributeBit_ & static_cast<uint32_t>(other);
}

uint32_t Attribute::Bit() const
{
	return attributeBit_;
}
