#include "TriangleCollider.h"
#include "PrimitiveCollisionDetection.h"

using YMath::Vector3;
using YMath::TriangleCollider;

TriangleCollider::TriangleCollider(
	Vector3* pFollowPoint,
	const std::array<Vector3, 3>& vertices,
	const Vector3& offset, const bool isSlip) :
	BasePrimitiveCollider(pFollowPoint, offset, isSlip),
	vertices_(vertices)
{
	CalcTriangleNormal();
}

TriangleCollider::TriangleCollider(
	Vector3* pFollowPoint, Vector3* pVelocity,
	const std::array<Vector3, 3>& vertices,
	const Vector3& offset, const bool isPushBack, const bool isSlip) :
	BasePrimitiveCollider(pFollowPoint, pVelocity, offset, isPushBack, isSlip),
	vertices_(vertices)
{
	CalcTriangleNormal();
}

void TriangleCollider::Initialize(
	Vector3* pFollowPoint,
	const std::array<Vector3, 3>& vertices,
	const Vector3& offset, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, offset, isSlip);
	vertices_ = vertices;
	CalcTriangleNormal();
}

void TriangleCollider::Initialize(
	Vector3* pFollowPoint, Vector3* pVelocity,
	const std::array<Vector3, 3>& vertices,
	const Vector3& offset, const bool isPushBack, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, pVelocity, offset, isPushBack, isSlip);
	vertices_ = vertices;
	CalcTriangleNormal();
}

void TriangleCollider::CalcTriangleNormal()
{
	Vector3 vecPos0ToPos1 = vertices_[1] - vertices_[0];
	Vector3 vecPos0ToPos2 = vertices_[2] - vertices_[0];

	normal_ = vecPos0ToPos1.Cross(vecPos0ToPos2).Normalized();
}

Vector3 TriangleCollider::VertexPos(const size_t index) const
{
	return *pFollowPoint_ + offset_ + vertices_[index];
}

bool TriangleCollider::CheckCollision(const BasePrimitiveCollider& other)
{
	if (isSlip_ || other.IsSlip()) { return false; }

	return other.CheckConcreteCollision(*this);
}

bool TriangleCollider::CheckConcreteCollision(const RayCollider& other) const
{
	return CollisionRayTriangle(other, *this);
}
bool TriangleCollider::CheckConcreteCollision(const SphereCollider& other) const
{
	return CollisionTriangleSphere(*this, other);
}