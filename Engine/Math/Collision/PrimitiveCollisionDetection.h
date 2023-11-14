#pragma once
#include "Vector2.h"
#include "BasePrimitiveCollider.h"
#include <array>

namespace YMath
{
	// 線 × 平面
	bool CollisionRayPlane(const RayCollider& ray, const PlaneCollider& plane);
	//bool CollisionRayPlane(const RayCollider& ray, const PlaneCollider& plane, float& distance, YMath::Vector3& inter);

	// 線 × 三角形
	bool CollisionRayTriangle(const RayCollider& ray, const TriangleCollider& triangle);

	// 線 × 球
	bool CollisionRaySphere(const RayCollider& ray, const SphereCollider& sphere);

	// 平面 × 球
	bool CollisionPlaneSphere(const PlaneCollider& plane, const SphereCollider& sphere);

	// 三角形 × 球
	bool CollisionTriangleSphere(const TriangleCollider& triangle, const SphereCollider& sphere);

	// 球 × 球
	bool CollisionSphereSphere(const SphereCollider& sphere1, const SphereCollider& sphere2);

	// 四角形[2D] × 四角形[2D]
	bool CollisionBoxBox2D(const Box2DCollider& box1, const Box2DCollider& box2);

	// 四角形[2D] × 四角形[2D]
	bool CollisionAndPushBackBoxBox2D(const Box2DCollider& box1, Box2DCollider& box2);
}
