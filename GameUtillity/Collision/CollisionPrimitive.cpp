#include "CollisionPrimitive.h"
#include "CollisionDetection.h"

using YMath::Vector3;

void YGame::Plane::SafeSetNormal(const YMath::Vector3& normal)
{
	normal_ = normal.Normalized();
}

void YGame::Ray::SafeSetDirection(const YMath::Vector3& direction)
{
	direction_ = direction.Normalized();
}

void YGame::Triangle::SafeSetNormal(const YMath::Vector3& normal)
{
	normal_ = normal.Normalized();
}

void YGame::Triangle::CalcNormal()
{
	Vector3 p0_p1 = p1_ - p0_;
	Vector3 p0_p2 = p2_ = p0_;

	// 外積 (2辺に垂直なベクトル)
	SafeSetNormal(p0_p1.Cross(p0_p2));
}

void YGame::Sphere::SafeSetRadius(const float rad)
{
	radius_ = rad >= 0 ? rad : -rad;
}

bool YGame::CollisionRayPlane(const Ray& ray, const Plane& plane)
{
	return YMath::CollisionRayPlane(ray.start_, ray.direction_, plane.normal_, plane.distance_);
}

bool YGame::CollisionRayTriangle(const Ray& ray, const Triangle& triangle)
{
	return YMath::CollisionRayTriangle(ray.start_, ray.direction_, triangle.p0_, triangle.p1_, triangle.p2_, triangle.normal_);
}

bool YGame::CollisionRaySphere(const Ray& ray, const Sphere& sphere)
{
	return YMath::CollisionRaySphere(ray.start_, ray.direction_, sphere.center_, sphere.radius_);
}

bool YGame::CollisionPlaneSphere(const Plane& plane, const Sphere& sphere)
{
	return YMath::CollisionPlaneSphere(plane.normal_, plane.distance_, sphere.center_, sphere.radius_);
}

bool YGame::CollisionTriangleSphere(const Triangle& triangle, const Sphere& sphere)
{
	return YMath::CollisionTriangleSphere(triangle.p0_, triangle.p1_, triangle.p2_, triangle.normal_, sphere.center_, sphere.radius_);
}
