#pragma once
#include "Vector2.h"
#include "Vector3.h"

namespace YMath
{
	// �A�^������ (���~����)
	bool CollisionRayPlane(
		const Vector3& rayStart, const Vector3& rayDirection,
		const Vector3& planeNormal, const float planeDist);
	// �A�^������ (���~����) <����,�^����_�擾ver>
	bool CollisionRayPlane(
		const Vector3& rayStart, const Vector3& rayDirection,
		const Vector3& planeNormal, const float planeDist,
		float& distance, Vector3& inter);

	// �A�^������ (���~�O�p�`)
	bool CollisionRayTriangle(
		const Vector3& rayStart, const Vector3& rayDirection,
		const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal);
	// �A�^������ (���~�O�p�`) <����,�^����_�擾ver>
	bool CollisionRayTriangle(
		const Vector3& rayStart, const Vector3& rayDirection,
		const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal,
		float& distance, Vector3& inter);

	// �A�^������ (���~��)
	bool CollisionRaySphere(
		const Vector3& rayStart, const Vector3& rayDirection,
		const Vector3& sphereCenter, const float sphereRad);
	// �A�^������ (���~��) <�ђʓ_�擾ver>
	bool CollisionRaySphere(
		const Vector3& rayStart, const Vector3& rayDirection,
		const Vector3& sphereCenter, const float sphereRad,
		float& distance, Vector3& start, Vector3& end);

	// �A�^������ (���ʁ~��)
	bool CollisionPlaneSphere(
		const Vector3& planeNormal, const float planeDist, 
		const Vector3& sphereCenter, const float sphereRad);
	// �A�^������ (���ʁ~��) <�^����_�擾ver>
	bool CollisionPlaneSphere(
		const Vector3& planeNormal, const float planeDist,
		const Vector3& sphereCenter, const float sphereRad,
		Vector3& inter);
	
	// �A�^������ (�O�p�`�~��)
	bool CollisionTriangleSphere(
		const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal,
		const Vector3& sphereCenter, const float sphereRad);
	// �A�^������ (�O�p�`�~��) <�^����_�擾ver>
	bool CollisionTriangleSphere(
		const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal,
		const Vector3& sphereCenter, const float sphereRad,
		Vector3& inter);

	// �A�^������ (���~��)
	bool CollisionSphereSphere(
		const Vector3& sphereCenter1, const float sphereRad1,
		const Vector3& sphereCenter2, const float sphereRad2
	);
}

