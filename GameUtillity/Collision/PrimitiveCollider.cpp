#include "PrimitiveCollider.h"

using YMath::Vector3;
using YGame::SphereCollider;

void SphereCollider::Initialize(
	const YMath::Vector3& center, const float radius, 
	YMath::Vector3 offset, uint32_t attribute, uint32_t mask, bool isInvincible)
{
	center_ = center;
	SafeSetRadius(radius);
	radius_ = radius;
	offset_ = offset;
	attribute_ = attribute;
	mask_ = mask;
	isInvincible_ = isInvincible;
	shape_ = ShapeType::CollsionShapeSphere;
}