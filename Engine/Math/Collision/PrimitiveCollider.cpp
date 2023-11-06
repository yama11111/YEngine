#include "PrimitiveCollider.h"
#include "CollisionDetection.h"
#include <cmath>

using YMath::Vector2;
using YMath::Vector3;
using YMath::RayCollider;
using YMath::PlaneCollider;
using YMath::TriangleCollider;
using YMath::SphereCollider;
using YMath::Box2DCollider;

#pragma region RayCollider

RayCollider::RayCollider(
	Vector3* pFollowPoint, 
	const Vector3& direction, 
	const Vector3& offset, const bool isSlip) : 
	BasePrimitiveCollider(pFollowPoint, offset, isSlip), 
	direction_(direction.Normalized())
{
}

RayCollider::RayCollider(
	Vector3* pFollowPoint, Vector3* pVelocity, 
	const Vector3& direction, 
	const Vector3& offset, const bool isPushBack, const bool isSlip) : 
	BasePrimitiveCollider(pFollowPoint, pVelocity, offset, isPushBack, isSlip), 
	direction_(direction.Normalized())
{
}

void RayCollider::Initialize(
	Vector3* pFollowPoint, 
	const Vector3& direction, 
	const Vector3& offset, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, offset, isSlip);
	direction_ = direction.Normalized();
}

void RayCollider::Initialize(
	Vector3* pFollowPoint, Vector3* pVelocity, 
	const Vector3& direction, 
	const Vector3& offset, const bool isPushBack, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, pVelocity, offset, isPushBack, isSlip);
	direction_ = direction.Normalized();
}

Vector3 RayCollider::Start() const
{
	return *pFollowPoint_ + offset_;
}

bool RayCollider::CheckCollision(const BasePrimitiveCollider& other) const
{ 
	if (isSlip_ || other.IsSlip()) { return false; }

	return other.CheckConcreteCollision(*this);
}
bool RayCollider::CheckConcreteCollision(const PlaneCollider& other) const 
{
	return CollisionRayPlane(*this, other);
}
bool RayCollider::CheckConcreteCollision(const TriangleCollider& other) const 
{
	return CollisionRayTriangle(*this, other);
}
bool RayCollider::CheckConcreteCollision(const SphereCollider& other) const 
{
	return CollisionRaySphere(*this, other);
}

#pragma endregion 


#pragma region PlaneCollider

PlaneCollider::PlaneCollider(
	Vector3* pFollowPoint, const 
	Vector3& normal, const float distance, const Vector2& rectangle, 
	const Vector3& offset, const bool isSlip) : 
	BasePrimitiveCollider(pFollowPoint, offset, isSlip), 
	normal_(normal.Normalized()), distance_(distance), rectangle_(rectangle)
{
}

PlaneCollider::PlaneCollider(
	Vector3* pFollowPoint, Vector3* pVelocity,
	const Vector3& normal, const float distance, const Vector2& rectangle,
	const Vector3& offset, const bool isPushBack, const bool isSlip) :
	BasePrimitiveCollider(pFollowPoint, pVelocity, offset, isPushBack, isSlip), 
	normal_(normal.Normalized()), distance_(distance), rectangle_(rectangle)
{
}

void PlaneCollider::Initialize(
	Vector3* pFollowPoint, 
	const Vector3& normal, const float distance, const Vector2& rectangle, 
	const Vector3& offset, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, offset, isSlip);
	normal_ = normal;
	distance_ = distance;
	rectangle_ = rectangle;
}

void PlaneCollider::Initialize(
	Vector3* pFollowPoint, Vector3* pVelocity,
	const Vector3& normal, const float distance, const Vector2& rectangle,
	const Vector3& offset, const bool isPushBack, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, pVelocity, offset, isPushBack, isSlip);
	normal_ = normal;
	distance_ = distance;
	rectangle_ = rectangle;
}

bool PlaneCollider::CheckCollision(const BasePrimitiveCollider& other) const
{
	if (isSlip_ || other.IsSlip()) { return false; }

	return other.CheckConcreteCollision(*this);
}

bool PlaneCollider::CheckConcreteCollision(const RayCollider& other) const 
{
	return CollisionRayPlane(other, *this);
}
bool PlaneCollider::CheckConcreteCollision(const SphereCollider& other) const 
{
	return CollisionPlaneSphere(*this, other);
}

#pragma endregion 


#pragma region TriangleCollider

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

bool TriangleCollider::CheckCollision(const BasePrimitiveCollider& other) const
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

#pragma endregion 


#pragma region SphererCollider

SphereCollider::SphereCollider(
	Vector3* pFollowPoint, 
	const float radius, 
	const Vector3& offset, const bool isSlip) : 
	BasePrimitiveCollider(pFollowPoint, offset, isSlip),
	radius_(fabsf(radius))
{
}

SphereCollider::SphereCollider(
	Vector3* pFollowPoint, Vector3* pVelocity,
	const float radius,
	const Vector3& offset, const bool isPushBack, const bool isSlip) : 
	BasePrimitiveCollider(pFollowPoint, pVelocity, offset, isPushBack, isSlip),
	radius_(fabsf(radius))
{
}

void SphereCollider::Initialize(
	Vector3* pFollowPoint,
	const float radius,
	const Vector3& offset, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, offset, isSlip);
	radius_ = fabsf(radius);
}

void SphereCollider::Initialize(
	Vector3* pFollowPoint, Vector3* pVelocity,
	const float radius,
	const Vector3& offset, const bool isPushBack, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, pVelocity, offset, isPushBack, isSlip);
	radius_ = fabsf(radius);
}

Vector3 SphereCollider::Center() const
{
	return *pFollowPoint_ + offset_;
}

bool SphereCollider::CheckCollision(const BasePrimitiveCollider& other) const
{
	if (isSlip_ || other.IsSlip()) { return false; }

	return other.CheckConcreteCollision(*this);
}

bool SphereCollider::CheckConcreteCollision(const RayCollider& other) const 
{
	return CollisionRaySphere(other, *this);
}
bool SphereCollider::CheckConcreteCollision(const PlaneCollider& other) const 
{
	return CollisionPlaneSphere(other, *this);
}
bool SphereCollider::CheckConcreteCollision(const TriangleCollider& other) const 
{
	return CollisionTriangleSphere(other, *this);
}
bool SphereCollider::CheckConcreteCollision(const SphereCollider& other) const 
{
	return CollisionSphereSphere(*this, other);
}

#pragma endregion 


#pragma region Box2DCollider

Box2DCollider::Box2DCollider(
	Vector3* pFollowPoint, 
	const Vector2& rectSize, 
	const Vector3& offset, const bool isSlip) : 
	BasePrimitiveCollider(pFollowPoint, offset, isSlip),
	rectSize_(Vector2(fabsf(rectSize.x_), fabsf(rectSize.y_)))
{
}

Box2DCollider::Box2DCollider(
	Vector3* pFollowPoint, Vector3* pVelocity,
	const Vector2& rectSize,
	const Vector3& offset, const bool isPushBack, const bool isSlip) : 
	BasePrimitiveCollider(pFollowPoint, pVelocity, offset, isPushBack, isSlip),
	rectSize_(Vector2(fabsf(rectSize.x_), fabsf(rectSize.y_)))
{
}

void Box2DCollider::Initialize(
	Vector3* pFollowPoint,
	const Vector2& rectSize,
	const Vector3& offset, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, offset, isSlip);
	rectSize_ = Vector2(fabsf(rectSize.x_), fabsf(rectSize.y_));
}

void Box2DCollider::Initialize(
	Vector3* pFollowPoint, Vector3* pVelocity,
	const Vector2& rectSize,
	const Vector3& offset, const bool isPushBack, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, pVelocity, offset, isPushBack, isSlip);
	rectSize_ = Vector2(fabsf(rectSize.x_), fabsf(rectSize.y_));
}

Vector2 Box2DCollider::Center() const
{
	return Vector2(pFollowPoint_->x_, pFollowPoint_->y_) + Vector2(offset_.x_, offset_.y_);
}

bool Box2DCollider::CheckCollision(const BasePrimitiveCollider& other) const
{
	if (isSlip_ || other.IsSlip()) { return false; }

	return other.CheckConcreteCollision(*this);
}
bool Box2DCollider::CheckConcreteCollision(const Box2DCollider& other) const 
{
	return CollisionBoxBox2D(*this, other);
}

#pragma endregion 


bool YMath::CollisionRayPlane(const RayCollider& ray, const PlaneCollider& plane)
{
	return YMath::CollisionRayPlane(
		ray.Start(), ray.Direction(),
		plane.Normal(), plane.Distance());
}

//bool YMath::CollisionRayPlane(const RayCollider& ray, const PlaneCollider& plane, float& distance, Vector3& inter)
//{
//	return YMath::CollisionRayPlane(
//		ray.Start(), ray.Direction(),
//		plane.Normal(), plane.Distance(),
//		distance, inter);
//}

bool YMath::CollisionRayTriangle(const RayCollider& ray, const TriangleCollider& triangle)
{
	return YMath::CollisionRayTriangle(
		ray.Start(), ray.Direction(),
		triangle.VertexPos(0), triangle.VertexPos(1), triangle.VertexPos(2), triangle.Normal());
}

bool YMath::CollisionRaySphere(const RayCollider& ray, const SphereCollider& sphere)
{
	return YMath::CollisionRaySphere(
		ray.Start(), ray.Direction(),
		sphere.Center(), sphere.Radius());
}

bool YMath::CollisionPlaneSphere(const PlaneCollider& plane, const SphereCollider& sphere)
{
	return YMath::CollisionPlaneSphere(
		plane.Normal(), plane.Distance(),
		sphere.Center(), sphere.Radius());
}

bool YMath::CollisionTriangleSphere(const TriangleCollider& triangle, const SphereCollider& sphere)
{
	return YMath::CollisionTriangleSphere(
		triangle.VertexPos(0), triangle.VertexPos(1), triangle.VertexPos(2), triangle.Normal(),
		sphere.Center(), sphere.Radius());
}

bool YMath::CollisionSphereSphere(const SphereCollider& sphere1, const SphereCollider& sphere2)
{
	return YMath::CollisionSphereSphere(
		sphere1.Center(), sphere1.Radius(),
		sphere2.Center(), sphere2.Radius());
}

bool YMath::CollisionBoxBox2D(const Box2DCollider& box1, const Box2DCollider& box2)
{
	return YMath::CollisionBoxBox2D(
		box1.Center(), box1.RectSize(),
		box2.Center(), box2.RectSize());
}

