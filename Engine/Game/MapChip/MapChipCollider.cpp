#include "MapChipCollider.h"
#include "MapChipCollisionBitConfig.h"

using YGame::MapChipCollider;

void MapChipCollider::Initialize(const YMath::Vector3& scale, const bool isBounce)
{
	scale_ = scale;
	collisionBit_ = ChipCollisionBit::kNone;
	isBounce_ = isBounce;
}