#pragma once
#include "Vec2.h"
#include "Vec3.h"

namespace YMath
{
	// �A�^������ (���ʁ~��)
	bool CollisonPlaneSphere(
		const Vec3& planeNormal, const float planeDist, 
		const Vec3& sphereCenter, const float sphereRad);
	// �A�^������ (���ʁ~��) <�^����_�擾ver>
	bool CollisonPlaneSphere(
		const Vec3& planeNormal, const float planeDist,
		const Vec3& sphereCenter, const float sphereRad,
		Vec3& inter);
	
	// �A�^������ (�O�p�`�~��)
	bool CollisonTriangleSphere(
		const Vec3& triPos0, const Vec3& triPos1, const Vec3& triPos2, const Vec3& triNormal,
		const Vec3& sphereCenter, const float sphereRad);
	// �A�^������ (�O�p�`�~��) <�^����_�擾ver>
	bool CollisonTriangleSphere(
		const Vec3& triPos0, const Vec3& triPos1, const Vec3& triPos2, const Vec3& triNormal,
		const Vec3& sphereCenter, const float sphereRad,
		Vec3& inter);

	// �A�^������ (���~��)
	bool CollisonRaySphere(
		const Vec3& rayPos, const Vec3& rayVelo, 
		const Vec3& spherePos, const float sphereRad);
	// �A�^������ (���~��) <�ђʓ_�擾ver>
	bool CollisonRaySphere(
		const Vec3& rayPos, const Vec3& rayVelo,
		const Vec3& spherePos, const float sphereRad,
		Vec3& start, Vec3& end);
}

