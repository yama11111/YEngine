#include "CollisionDetection.h"
#include <cmath>

using YMath::Vec3;

#pragma region ���� �� ��

bool YMath::CollisonPlaneSphere(
	const Vec3& planeNormal, const float planeDist, 
	const Vec3& sphereCenter, const float sphereRad)
{
	// ���_ �� �� �̋���
	float sphereDist = sphereCenter.Dot(planeNormal);
	
	// (�� - ����) = �� �� ���� �̋���
	float dist = sphereDist - planeDist;

	// (����(��Βl) > ���̔��a) = �������ĂȂ�
	if (fabsf(dist) > sphereRad) { return false; }

	return true;
}
bool YMath::CollisonPlaneSphere(
	const Vec3& planeNormal, const float planeDist, 
	const Vec3& sphereCenter, const float sphereRad,
	Vec3& inter)
{
	// ���_ �� �� �̋���
	float sphereDist = sphereCenter.Dot(planeNormal);

	// (�� - ����) = �� �� ���� �̋���
	float dist = sphereDist - planeDist;

	// ����(��Βl) > ���̔��a = �������ĂȂ�
	if (fabsf(dist) > sphereRad) { return false; }

	// �^����_ (���ʏ�̍ŋߐړ_)
	inter = -dist * planeNormal + sphereCenter;

	return true;
}

#pragma endregion


#pragma region �O�p�` �� ��

static YMath::Vec3 ClosestPointTriangle(const Vec3& point, const Vec3& triPos0, const Vec3& triPos1, const Vec3& triPos2)
{
	// p0 �� �O�� ��
	Vec3 p0_p1 = triPos1 - triPos0;
	Vec3 p0_p2 = triPos2 - triPos0;
	Vec3 p0_pt = point - triPos0;

	float d1 = p0_p1.Dot(p0_pt);
	float d2 = p0_p2.Dot(p0_pt);

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// p0 �� �ŋߖT
		return triPos0;
	}

	// p1 �� �O�� ��
	Vec3 p1_pt = point - triPos1;

	float d3 = p0_p1.Dot(p1_pt);
	float d4 = p0_p2.Dot(p1_pt);

	if (d3 >= 0.0f && d4 <= d3)
	{
		// p1 �� �ŋߖT
		return triPos1;
	}

	// p0_p1 �� ������
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		// p0_p1 ��ɑ΂���ˉe��Ԃ�
		float v = d1 / (d1 - d3);
		return triPos0 + v * p0_p1;
	}

	// p2 �� �O����
	Vec3 p2_pt = point - triPos2;

	float d5 = p0_p1.Dot(p2_pt);
	float d6 = p0_p2.Dot(p2_pt);
	if (d6 >= 0.0f && d5 <= d6)
	{
		// p2 �� �ŋߖT
		return triPos2;
	}

	// p0_p2 �� ������ 
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		// p0_p2 ��ɑ΂���ˉe��Ԃ�
		float w = d2 / (d2 - d6);
		return triPos0 + w * p0_p2;
	}

	// p1_p2 �� ������
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		// p1_p2 ��ɑ΂���ˉe��Ԃ�
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		return triPos1 + w * (triPos2 - triPos1);
	}


	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom;
	float w = vc * denom;
	return triPos0 + p0_p1 * v + p0_p2 * w;
}

bool YMath::CollisonTriangleSphere(
	const Vec3& triPos0, const Vec3& triPos1, const Vec3& triPos2, const Vec3& triNormal,
	const Vec3& sphereCenter, const float sphereRad)
{
	// �� �� �O�p�`�� �� �ŋߐړ_
	Vec3 closest = ClosestPointTriangle(sphereCenter, triPos0, triPos1, triPos2);
	
	// �� �� �ŋߐړ_
	Vec3 v = closest - sphereCenter;
	
	// (�� �� �ŋߐړ_) ^ 2 > ���̔��a ^ 2 = �������ĂȂ�
	if (v.Dot(v) > sphereRad * sphereRad) { return false; }

	return true;
}
bool YMath::CollisonTriangleSphere(
	const Vec3& triPos0, const Vec3& triPos1, const Vec3& triPos2, const Vec3& triNormal,
	const Vec3& sphereCenter, const float sphereRad, 
	Vec3& inter)
{
	// �� �� �O�p�`�� �� �ŋߐړ_
	Vec3 closest = ClosestPointTriangle(sphereCenter, triPos0, triPos1, triPos2);

	// �� �� �ŋߐړ_
	Vec3 v = closest - sphereCenter;

	// (�� �� �ŋߐړ_) ^ 2 > ���̔��a ^ 2 = �������ĂȂ�
	if (v.Dot(v) > sphereRad * sphereRad) { return false; }

	// �^����_ (�O�p�`��̍ŋߐړ_)
	inter = closest;

	return true;
}

#pragma endregion


#pragma region �� �� ��

bool YMath::CollisonRaySphere(
	const Vec3& rayPos, const Vec3& rayVelo,
	const Vec3& spherePos, const float sphereRad)
{
	Vec3 p = spherePos - rayPos;

	float a = rayVelo.Dot(rayVelo);
	if (a == 0.0f) { return false; }
	float b = rayVelo.Dot(p);
	float c = p.Dot(p) - (sphereRad * sphereRad);

	float s = b * b - a * c;
	if (s < 0.0f) { return false; }

	float a1 = (b - sqrtf(s)) / a;
	float a2 = (b + sqrtf(s)) / a;
	if (a1 < 0.0f || a2 < 0.0f) { return false; }

	return true;
}
bool YMath::CollisonRaySphere(
	const Vec3& rayPos, const Vec3& rayVelo,
	const Vec3& spherePos, const float sphereRad,
	Vec3& start, Vec3& end)
{
	Vec3 p = spherePos - rayPos;

	float a = rayVelo.Dot(rayVelo);
	if (a == 0.0f) { return false; }
	float b = rayVelo.Dot(p);
	float c = p.Dot(p) - (sphereRad * sphereRad);

	float s = b * b - a * c;
	if (s < 0.0f) { return false; }

	float a1 = (b - sqrtf(s)) / a;
	float a2 = (b + sqrtf(s)) / a;
	if (a1 < 0.0f || a2 < 0.0f) { return false; }

	start = rayPos + (a1 * rayVelo);
	end = rayPos + (a2 * rayVelo);

	return true;
}

#pragma endregion