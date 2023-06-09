#include "MapChipCollider.h"

using YGame::MapChipCollider;

void MapChipCollider::Initialize(const YMath::Vector3& scale)
{
	scale_ = scale;
	isLanding_ = false;
	isElderLanding_ = false;
}