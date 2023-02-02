#pragma once
#include "Vec2.h"
#include "Vec3.h"

namespace YMath
{
	// A^»θ (½Κ~)
	bool CollisonPlaneSphere(
		const Vec3& planeNormal, const float planeDist, 
		const Vec3& sphereCenter, const float sphereRad);
	// A^»θ (½Κ~) <^π_ζΎver>
	bool CollisonPlaneSphere(
		const Vec3& planeNormal, const float planeDist,
		const Vec3& sphereCenter, const float sphereRad,
		Vec3& inter);
	
	// A^»θ (Op`~)
	bool CollisonTriangleSphere(
		const Vec3& triPos0, const Vec3& triPos1, const Vec3& triPos2, const Vec3& triNormal,
		const Vec3& sphereCenter, const float sphereRad);
	// A^»θ (Op`~) <^π_ζΎver>
	bool CollisonTriangleSphere(
		const Vec3& triPos0, const Vec3& triPos1, const Vec3& triPos2, const Vec3& triNormal,
		const Vec3& sphereCenter, const float sphereRad,
		Vec3& inter);

	// A^»θ (ό~)
	bool CollisonRaySphere(
		const Vec3& rayPos, const Vec3& rayVelo, 
		const Vec3& spherePos, const float sphereRad);
	// A^»θ (ό~) <ΡΚ_ζΎver>
	bool CollisonRaySphere(
		const Vec3& rayPos, const Vec3& rayVelo,
		const Vec3& spherePos, const float sphereRad,
		Vec3& start, Vec3& end);
}

