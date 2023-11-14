#pragma once
#include "Vector2.h"
#include "Vector3.h"

namespace YMath
{
	// アタリ判定 (線×平面)
	bool CollisionRayPlane(
		const Vector3& rayStart, const Vector3& rayDirection,
		const Vector3& planeNormal, const float planeDist);
	// アタリ判定 (線×平面) <距離,疑似交点取得ver>
	bool CollisionRayPlane(
		const Vector3& rayStart, const Vector3& rayDirection,
		const Vector3& planeNormal, const float planeDist,
		float& distance, Vector3& inter);

	// アタリ判定 (線×三角形)
	bool CollisionRayTriangle(
		const Vector3& rayStart, const Vector3& rayDirection,
		const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal);
	// アタリ判定 (線×三角形) <距離,疑似交点取得ver>
	bool CollisionRayTriangle(
		const Vector3& rayStart, const Vector3& rayDirection,
		const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal,
		float& distance, Vector3& inter);

	// アタリ判定 (線×球)
	bool CollisionRaySphere(
		const Vector3& rayStart, const Vector3& rayDirection,
		const Vector3& sphereCenter, const float sphereRad);
	// アタリ判定 (線×球) <貫通点取得ver>
	bool CollisionRaySphere(
		const Vector3& rayStart, const Vector3& rayDirection,
		const Vector3& sphereCenter, const float sphereRad,
		float& distance, Vector3& start, Vector3& end);

	// アタリ判定 (平面×球)
	bool CollisionPlaneSphere(
		const Vector3& planeNormal, const float planeDist, 
		const Vector3& sphereCenter, const float sphereRad);
	// アタリ判定 (平面×球) <疑似交点取得ver>
	bool CollisionPlaneSphere(
		const Vector3& planeNormal, const float planeDist,
		const Vector3& sphereCenter, const float sphereRad,
		Vector3& inter);
	
	// アタリ判定 (三角形×球)
	bool CollisionTriangleSphere(
		const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal,
		const Vector3& sphereCenter, const float sphereRad);
	// アタリ判定 (三角形×球) <疑似交点取得ver>
	bool CollisionTriangleSphere(
		const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal,
		const Vector3& sphereCenter, const float sphereRad,
		Vector3& inter);

	// アタリ判定 (球×球)
	bool CollisionSphereSphere(
		const Vector3& sphereCenter1, const float sphereRad1,
		const Vector3& sphereCenter2, const float sphereRad2);


	// アタリ判定 (四角形×四角形) [2D]
	bool CollisionBoxBox2D(
		const Vector2& boxCenter1, const Vector2& boxRadSize1,
		const Vector2& boxCenter2, const Vector2& boxRadSize2);

	// アタリ判定 (四角形×四角形) [2D]
	bool CollisionAndPushBackBoxBox2D(
		const Vector3& followPoint1, const Vector3& velocity1, const Vector2& boxRadSize1,
		Vector3* pFollowPoint2, Vector3* pVelocity2, const Vector2& boxRadSize2);
}

