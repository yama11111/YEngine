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

RayCollider::RayCollider(const Vector3& start, const Vector3& direction, const bool isSlip) : 
	BasePrimitiveCollider(isSlip),
	start_(start), direction_(direction.Normalized())
{
}
RayCollider::RayCollider(Vector3* pFollowPoint, const Vector3& offset, const Vector3& direction, const bool isSlip) :
	BasePrimitiveCollider(pFollowPoint, offset, isSlip),
	start_(Vector3()), direction_(direction.Normalized())
{
}

void RayCollider::Initialize(const Vector3& start, const Vector3& direction, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(nullptr, Vector3(), isSlip);

	start_ = start;
	direction_ = direction;
}
void RayCollider::Initialize(Vector3* pFollowPoint, const Vector3& offset, const Vector3& direction, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, offset, isSlip);

	direction_ = direction;
}

Vector3 RayCollider::Start() const
{
	if (pFollowPoint_)
	{
		return *pFollowPoint_ + offset_ + start_;
	}

	return start_;
}

bool RayCollider::CheckCollision(const BasePrimitiveCollider& other) const
{
	//  ǂ  炩   蔲    Ȃ e  
	if (isSlip_ || other.isSlip_) { return false; }

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

PlaneCollider::PlaneCollider(const YMath::Vector3& normal, const float distance, const bool isSlip) : 
	BasePrimitiveCollider(isSlip),
	normal_(normal.Normalized()), distance_(distance)
{
}

void PlaneCollider::Initialize(const Vector3& normal, const float distance, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(nullptr, Vector3(), isSlip);

	distance_ = distance;
	isSlip_ = isSlip;
}

bool PlaneCollider::CheckCollision(const BasePrimitiveCollider& other) const
{
	//  ǂ  炩   蔲    Ȃ e  
	if (isSlip_ || other.isSlip_) { return false; }

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

TriangleCollider::TriangleCollider(const std::array<Vector3, 3>& vertices, const bool isSlip) : 
	BasePrimitiveCollider(isSlip), 
	vertices_(vertices)
{
	CalcTriangleNormal();
}
TriangleCollider::TriangleCollider(Vector3* pFollowPoint, const Vector3& offset, 
	const std::array<Vector3, 3>& vertices, const bool isSlip) :
	BasePrimitiveCollider(pFollowPoint, offset, isSlip),
	vertices_(vertices)
{
	CalcTriangleNormal();
}

void TriangleCollider::Initialize(const std::array<Vector3, 3>& vertices, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(nullptr, Vector3(), isSlip);

	vertices_ = vertices;
	isSlip_ = isSlip;
}
void TriangleCollider::Initialize(Vector3* pFollowPoint, const Vector3& offset, 
	const std::array<Vector3, 3>& vertices, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, offset, isSlip);

	vertices_ = vertices;
	isSlip_ = isSlip;
}

void TriangleCollider::CalcTriangleNormal()
{
	Vector3 vecPos0ToPos1 = vertices_[1] - vertices_[0];
	Vector3 vecPos0ToPos2 = vertices_[2] - vertices_[0];

	//  O   (2 ӂɐ    ȃx N g  )
	normal_ = vecPos0ToPos1.Cross(vecPos0ToPos2).Normalized();
}
Vector3 TriangleCollider::VertexPos(const size_t index) const
{
	if (pFollowPoint_)
	{
		return *pFollowPoint_ + offset_ + vertices_[index];
	}

	return vertices_[index];
}

bool TriangleCollider::CheckCollision(const BasePrimitiveCollider& other) const
{
	//  ǂ  炩   蔲    Ȃ e  
	if (isSlip_ || other.isSlip_) { return false; }

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

SphereCollider::SphereCollider(const Vector3& center, const float radius, const bool isSlip) : 
	BasePrimitiveCollider(isSlip),
	center_(center), radius_(fabsf(radius))
{
}
SphereCollider::SphereCollider(Vector3* pFollowPoint, const Vector3& offset, const float radius, const bool isSlip) : 
	BasePrimitiveCollider(pFollowPoint, offset, isSlip),
	center_(Vector3()), radius_(fabsf(radius))
{
}

void SphereCollider::Initialize(const Vector3& center, const float radius, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(nullptr, Vector3(), isSlip);

	center_ = center;
	radius_ = fabsf(radius);
}
void SphereCollider::Initialize(Vector3* pFollowPoint, const Vector3& offset, const float radius, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, offset, isSlip);

	radius_ = fabsf(radius);
}

Vector3 SphereCollider::Center() const
{
	if (pFollowPoint_)
	{
		return *pFollowPoint_ + offset_ + center_;
	}

	return center_;
}

bool SphereCollider::CheckCollision(const BasePrimitiveCollider& other) const
{
	//  ǂ  炩   蔲    Ȃ e  
	if (isSlip_ || other.isSlip_) { return false; }

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

Box2DCollider::Box2DCollider(const Vector2& center, const Vector2& radSize, const bool isSlip) : 
	BasePrimitiveCollider(isSlip),
	center_(center), radSize_(Vector2(fabsf(radSize.x_), fabsf(radSize.y_)))
{
}
Box2DCollider::Box2DCollider(Vector3* pFollowPoint, const Vector3& offset, const Vector2& radSize, const bool isSlip) :
	BasePrimitiveCollider(pFollowPoint, offset, isSlip),
	center_(Vector2()), radSize_(Vector2(fabsf(radSize.x_), fabsf(radSize.y_)))

{
}

void Box2DCollider::Initialize(const Vector2& center, const Vector2& radSize, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(nullptr, Vector3(), isSlip);

	center_ = center;
	radSize_ = Vector2(fabsf(radSize.x_), fabsf(radSize.y_));
}
void Box2DCollider::Initialize(Vector3* pFollowPoint, const Vector3& offset, const Vector2& radSize, const bool isSlip)
{
	BasePrimitiveCollider::Initialize(pFollowPoint, offset, isSlip);

	radSize_ = Vector2(fabsf(radSize.x_), fabsf(radSize.y_));
}

Vector2 Box2DCollider::Center() const
{
	if (pFollowPoint_)
	{
		return Vector2(pFollowPoint_->x_, pFollowPoint_->y_) + Vector2(offset_.x_, offset_.y_) + center_;
	}

	return center_;
}

bool Box2DCollider::CheckCollision(const BasePrimitiveCollider& other) const
{
	//  ǂ  炩   蔲    Ȃ e  
	if (isSlip_ || other.isSlip_) { return false; }

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

bool YMath::CollisionRayPlane(const RayCollider& ray, const PlaneCollider& plane, float& distance, Vector3& inter)
{
	return YMath::CollisionRayPlane(
		ray.Start(), ray.Direction(),
		plane.Normal(), plane.Distance(),
		distance, inter);
}

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
		box1.Center(), box1.RadSize(),
		box2.Center(), box2.RadSize());
}

