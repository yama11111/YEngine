#pragma once
#include "Vec2.h"
#include "Vec3.h"

namespace YMath
{
	// アタリ判定 (平面×球)
	bool CollisonPlaneSphere(
		const Vec3& planeNormal, const float planeDist, 
		const Vec3& sphereCenter, const float sphereRad);
	// アタリ判定 (平面×球) <疑似交点取得ver>
	bool CollisonPlaneSphere(
		const Vec3& planeNormal, const float planeDist,
		const Vec3& sphereCenter, const float sphereRad,
		Vec3& inter);
	
	// アタリ判定 (三角形×球)
	bool CollisonTriangleSphere(
		const Vec3& triPos0, const Vec3& triPos1, const Vec3& triPos2, const Vec3& triNormal,
		const Vec3& sphereCenter, const float sphereRad);
	// アタリ判定 (三角形×球) <疑似交点取得ver>
	bool CollisonTriangleSphere(
		const Vec3& triPos0, const Vec3& triPos1, const Vec3& triPos2, const Vec3& triNormal,
		const Vec3& sphereCenter, const float sphereRad,
		Vec3& inter);

	// アタリ判定 (線×球)
	bool CollisonRaySphere(
		const Vec3& rayPos, const Vec3& rayVelo, 
		const Vec3& spherePos, const float sphereRad);
	// アタリ判定 (線×球) <貫通点取得ver>
	bool CollisonRaySphere(
		const Vec3& rayPos, const Vec3& rayVelo,
		const Vec3& spherePos, const float sphereRad,
		Vec3& start, Vec3& end);
}

