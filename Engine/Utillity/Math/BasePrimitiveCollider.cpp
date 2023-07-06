#include "BasePrimitiveCollider.h"

using YMath::BasePrimitiveCollider;
using YMath::Vector3;

void BasePrimitiveCollider::Initialize(Vector3* pFollowPoint, const Vector3& offset, const bool isSlip)
{
	pFollowPoint_ = pFollowPoint;
	offset_ = offset;
	isSlip_ = isSlip;
}

BasePrimitiveCollider::BasePrimitiveCollider(const bool isSlip) : 
	pFollowPoint_(nullptr), offset_(Vector3()), isSlip_(isSlip)
{
}

BasePrimitiveCollider::BasePrimitiveCollider(Vector3* pFollowPoint, const Vector3& offset, const bool isSlip) :
	pFollowPoint_(pFollowPoint), offset_(offset), isSlip_(isSlip)
{
}
