#include "CollisionPrimitive.h"
#include "CollisionDetection.h"

using YMath::Vec3;

void YCollision::Plane::SafeSetNormal(const YMath::Vec3& normal)
{
	normal_ = normal.Normalized();
}

void YCollision::Triangle::SafeSetNormal(const YMath::Vec3& normal)
{
	normal_ = normal.Normalized();
}

void YCollision::Sphere::SafeSetRadius(const float rad)
{
	radius_ = rad >= 0 ? rad : -rad;
}

bool YCollision::CollisonPlaneSphere(const Plane& plane, const Sphere& sphere)
{
	return YMath::CollisonPlaneSphere(plane.normal_, plane.distance_, sphere.center_, sphere.radius_);
}

bool YCollision::CollisionTriangleSphere(const Triangle& triangle, const Sphere& sphere)
{
	return YMath::CollisonTriangleSphere(triangle.p0_, triangle.p1_, triangle.p2_, triangle.normal_, sphere.center_, sphere.radius_);
}
