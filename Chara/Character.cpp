#include "Character.h"
#include <cassert>

MapChipPointer* Character::pMapChip_ = nullptr;

void Character::SetMapChipPointer(MapChipPointer* pMapChip)
{
	assert(pMapChip);
	pMapChip_ = pMapChip;
}
