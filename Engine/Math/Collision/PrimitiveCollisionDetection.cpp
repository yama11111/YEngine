#include "PrimitiveCollisionDetection.h"
#include "CollisionDetection.h"

#include "RayCollider.h"
#include "PlaneCollider.h"
#include "TriangleCollider.h"
#include "SphereCollider.h"
#include "Box2DCollider.h"

#include <cmath>

using YMath::Vector2;
using YMath::Vector3;

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

bool YMath::CollisionAndPushBackBoxBox2D(const Box2DCollider& box1, Box2DCollider& box2)
{
	return YMath::CollisionAndPushBackBoxBox2D(
		box1.FollowPoint(), box1.Velocity(), box1.RectSize(),
		box2.FollowPointPtr(), box2.VelocityPtr(), box2.RectSize());
}

