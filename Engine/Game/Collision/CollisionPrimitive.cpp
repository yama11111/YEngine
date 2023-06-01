#include "CollisionPrimitive.h"
#include "CollisionDetection.h"
#include <cmath>

using YMath::Vector2;
using YMath::Vector3;
using YGame::Ray;
using YGame::Plane;
using YGame::Triangle;
using YGame::Sphere;
using YGame::Box2D;

void Ray::SetRayStart(const Vector3& start)
{
	start_ = start;
}
void Ray::SetRayDirection(const Vector3& direction)
{
	direction_ = direction.Normalized();
}

void Plane::SetPlaneNormal(const Vector3& normal)
{
	normal_ = normal.Normalized();
}
void Plane::SetPlaneDistance(const float distance)
{
	distance_ = distance;
}

void Triangle::SetTrianglePos(const Vector3& p0, const Vector3& p1, const Vector3& p2)
{
	p0_ = p0;
	p1_ = p1;
	p2_ = p2;
}
void Triangle::SetTriangleNormal(const Vector3& normal)
{
	normal_ = normal.Normalized();
}
void Triangle::CalcTriangleNormal()
{
	Vector3 p0_p1 = p1_ - p0_;
	Vector3 p0_p2 = p2_ = p0_;

	// 外積 (2辺に垂直なベクトル)
	SetTriangleNormal(p0_p1.Cross(p0_p2));
}

void Sphere::SetSphereCenter(const Vector3& center)
{
	center_ = center;
}
void Sphere::SetSphereRadius(const float radius)
{
	radius_ = fabs(radius);
}
Vector3 Triangle::GetTrianglePos(const size_t index) const 
{
	YMath::Vector3 result;

	if (index == 0) { result = p0_; }
	if (index == 1) { result = p1_; }
	if (index == 2) { result = p2_; }

	return result;
}

void Box2D::SetBox2DCenter(const Vector2& center)
{
	center_ = center;
}
void Box2D::SetBox2DRadSize(const Vector2& radSize)
{
	radSize_.x_ = fabs(radSize.x_);
	radSize_.y_ = fabs(radSize.y_);
}


bool YGame::CollisionRayPlane(const Ray& ray, const Plane& plane)
{
	return YMath::CollisionRayPlane(
		ray.GetRayStart(), ray.GetRayDirection(), 
		plane.GetPlaneNormal(), plane.GetPlaneDistance());
}

bool YGame::CollisionRayPlane(const Ray& ray, const Plane& plane, float& distance, Vector3& inter)
{
	return YMath::CollisionRayPlane(
		ray.GetRayStart(), ray.GetRayDirection(),
		plane.GetPlaneNormal(), plane.GetPlaneDistance(), 
		distance, inter);
}

bool YGame::CollisionRayTriangle(const Ray& ray, const Triangle& triangle)
{
	return YMath::CollisionRayTriangle(
		ray.GetRayStart(), ray.GetRayDirection(), 
		triangle.GetTrianglePos(0), triangle.GetTrianglePos(1), triangle.GetTrianglePos(2), triangle.GetTriangleNormal());
}

bool YGame::CollisionRaySphere(const Ray& ray, const Sphere& sphere)
{
	return YMath::CollisionRaySphere(
		ray.GetRayStart(), ray.GetRayDirection(), 
		sphere.GetSphereCenter(), sphere.GetSphereRadius());
}

bool YGame::CollisionPlaneSphere(const Plane& plane, const Sphere& sphere)
{
	return YMath::CollisionPlaneSphere(
		plane.GetPlaneNormal(), plane.GetPlaneDistance(),
		sphere.GetSphereCenter(), sphere.GetSphereRadius());
}

bool YGame::CollisionTriangleSphere(const Triangle& triangle, const Sphere& sphere)
{
	return YMath::CollisionTriangleSphere(
		triangle.GetTrianglePos(0), triangle.GetTrianglePos(1), triangle.GetTrianglePos(2), triangle.GetTriangleNormal(), 
		sphere.GetSphereCenter(), sphere.GetSphereRadius());
}

bool YGame::CollisionSphereSphere(const Sphere& sphere1, const Sphere& sphere2)
{
	return YMath::CollisionSphereSphere(
		sphere1.GetSphereCenter(), sphere1.GetSphereRadius(), 
		sphere2.GetSphereCenter(), sphere2.GetSphereRadius());
}

bool YGame::CollisionBoxBox2D(const Box2D& box1, const Box2D& box2)
{
	return YMath::CollisionBoxBox2D(
		box1.GetBox2DCenter(), box1.GetBox2DRadSize(),
		box2.GetBox2DCenter(), box2.GetBox2DRadSize());
}

