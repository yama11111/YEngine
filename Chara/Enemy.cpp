#include "Enemy.h"
#include "CollisionConfig.h"
#include "CalcTransform.h"
#include "MapChipManager.h"
#include "YMath.h"
#include <cassert>

MapChipPointer* Enemy::pMapChip_ = nullptr;

void Enemy::SetMapChipPointer(MapChipPointer* pMapChip)
{
	assert(pMapChip);
	pMapChip_ = pMapChip;
}

void Enemy::OnCollision(const uint32_t attribute)
{

}
