#include "MapChipCollider.h"
#include "MapChipCollisionBitConfig.h"

using YGame::MapChipCollider;

void MapChipCollider::Initialize(const YMath::Vector3& scale)
{
	scale_ = scale;
	collisionBit_ = ChipCollisionBit::kNone;
}