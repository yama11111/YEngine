#include "CollisionDetection.h"
#include <cmath>

using YMath::Vector3;

static const float Epsilon = 1.0e-5f;

#pragma region ���ƕ���

bool YMath::CollisionRayPlane(
	const Vector3& rayStart, const Vector3& rayDirection,
	const Vector3& planeNormal, const float planeDist)
{
	// �ʖ@���ƃ��C�̕����x�N�g���̓���
	float d1 = planeNormal.Dot(rayDirection);
	// ���ʂɂ͓�����Ȃ�
	if (d1 > -Epsilon) { return false; }

	// �n�_ �� ���_ (���ʂ̖@������)
	// �ʖ@�� �� ���C�̎��_���W (�ʒu�x�N�g��) �̓���
	float d2 = planeNormal.Dot(rayStart);

	// �n�_�ƕ��ʂ̋��� (���ʂ̖@������)
	float dist = d2 - planeDist;

	// �n�_�ƕ��ʂ̋��� (���C����)
	float t = dist / -d1;
	// ��_���n�_�����ɂ��� �� ������Ȃ�
	if (t < 0) { return false; }

	return true;
}

bool YMath::CollisionRayPlane(
	const Vector3& rayStart, const Vector3& rayDirection, 
	const Vector3& planeNormal, const float planeDist, 
	float& distance, Vector3& inter)
{
	// �ʖ@���ƃ��C�̕����x�N�g���̓���
	float d1 = planeNormal.Dot(rayDirection);
	// ���ʂɂ͓�����Ȃ�
	if (d1 > -Epsilon) { return false; }

	// �n�_ �� ���_ (���ʂ̖@������)
	// �ʖ@�� �� ���C�̎��_���W (�ʒu�x�N�g��) �̓���
	float d2 = planeNormal.Dot(rayStart);

	// �n�_�ƕ��ʂ̋��� (���ʂ̖@������)
	float dist = d2 - planeDist;

	// �n�_�ƕ��ʂ̋��� (���C����)
	float t = dist / -d1;
	// ��_���n�_�����ɂ��� �� ������Ȃ�
	if (t < 0) { return false; }
	
	// ����
	distance = t;
	// ��_
	inter = rayStart + (t * rayDirection);

	return true;
}

#pragma endregion


#pragma region ���ƎO�p�`

bool YMath::CollisionRayTriangle(
	const Vector3& rayStart, const Vector3& rayDirection,
	const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal)
{
	// �O�p�`�̕���
	Vector3 planeNormal = triNormal;
	float planeDist = triNormal.Dot(triPos0);
	float distance = 0.0f;
	Vector3 interPlane;

	// ���C �� ���ʂ��������Ă��邩
	if (CollisionRayPlane(rayStart, rayDirection, planeNormal, planeDist, distance, interPlane) == false)
	{
		return false;
	}

	// ���C �� ���ʂ̌�_ �� �O�p�`�̓�����
	// p0 �� p1
	Vector3 pt_p0 = triPos0 - interPlane;
	Vector3 p0_p1 = triPos1 - triPos0;
	Vector3 m1 = pt_p0.Cross(p0_p1);
	// �ӂ̊O�� �� ������Ȃ�
	if (m1.Dot(triNormal) < -Epsilon) { return false; }

	// p1 �� p2
	Vector3 pt_p1 = triPos1 - interPlane;
	Vector3 p1_p2 = triPos2 - triPos1;
	Vector3 m2 = pt_p1.Cross(p1_p2);
	// �ӂ̊O�� �� ������Ȃ�
	if (m2.Dot(triNormal) < -Epsilon) { return false; }

	// p2 �� p0
	Vector3 pt_p2 = triPos2 - interPlane;
	Vector3 p2_p0 = triPos2 - triPos0;
	Vector3 m3 = pt_p2.Cross(p2_p0);
	// �ӂ̊O�� �� ������Ȃ�
	if (m3.Dot(triNormal) < -Epsilon) { return false; }

	return true;
}

bool YMath::CollisionRayTriangle(
	const Vector3& rayStart, const Vector3& rayDirection,
	const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal,
	float& distance, Vector3& inter)
{
	// �O�p�`�̕���
	Vector3 planeNormal = triNormal;
	float planeDist = triNormal.Dot(triPos0);
	Vector3 interPlane;

	// ���C �� ���ʂ��������Ă��邩
	if (CollisionRayPlane(rayStart, rayDirection, planeNormal, planeDist, distance, interPlane) == false) 
	{
		return false; 
	}

	// ���C �� ���ʂ̌�_ �� �O�p�`�̓�����
	// p0 �� p1
	Vector3 pt_p0 = triPos0 - interPlane;
	Vector3 p0_p1 = triPos1 - triPos0;
	Vector3 m1 = pt_p0.Cross(p0_p1);
	// �ӂ̊O�� �� ������Ȃ�
	if (m1.Dot(triNormal) < -Epsilon) { return false; }

	// p1 �� p2
	Vector3 pt_p1 = triPos1 - interPlane;
	Vector3 p1_p2 = triPos2 - triPos1;
	Vector3 m2 = pt_p1.Cross(p1_p2);
	// �ӂ̊O�� �� ������Ȃ�
	if (m2.Dot(triNormal) < -Epsilon) { return false; }
	
	// p2 �� p0
	Vector3 pt_p2 = triPos2 - interPlane;
	Vector3 p2_p0 = triPos2 - triPos0;
	Vector3 m3 = pt_p2.Cross(p2_p0);
	// �ӂ̊O�� �� ������Ȃ�
	if (m3.Dot(triNormal) < -Epsilon) { return false; }

	// ����
	inter = interPlane;

	return true;
}

#pragma endregion


#pragma region ���Ƌ�

bool YMath::CollisionRaySphere(
	const Vector3& rayStart, const Vector3& rayDirection,
	const Vector3& sphereCenter, const float sphereRad)
{
	Vector3 m = rayStart - sphereCenter;
	float b = m.Dot(rayDirection);
	float c = m.Dot(m) - (sphereRad * sphereRad);
	// ���C�̎n�_ �� ���̊O�� (c > 0) && ���C �� �� ���痣��Ă������� (b > 0) �� ������Ȃ�
	if (c > 0.0f && b > 0.0f) { return false; }

	float discr = b * b - c;
	// �� �� ���C �� �� ���O��Ă��� �� ������Ȃ�
	if (discr < 0.0f) { return false; }

	// ����
	return true;
}
bool YMath::CollisionRaySphere(
	const Vector3& rayStart, const Vector3& rayDirection,
	const Vector3& sphereCenter, const float sphereRad,
	float& distance, Vector3& start, Vector3& end)
{
	//Vector3 p = sphereCenter - rayDirection;

	//float a = rayDirection.Dot(rayDirection);
	//if (a == 0.0f) { return false; }
	//float b = rayDirection.Dot(p);
	//float c = p.Dot(p) - (sphereRad * sphereRad);

	//float s = b * b - a * c;
	//if (s < 0.0f) { return false; }

	//float a1 = (b - sqrtf(s)) / a;
	//float a2 = (b + sqrtf(s)) / a;
	//if (a1 < 0.0f || a2 < 0.0f) { return false; }

	//start = rayPos + (a1 * rayVelo);
	//end = rayPos + (a2 * rayVelo);


	Vector3 m = rayStart - sphereCenter;
	float b = m.Dot(rayDirection);
	float c = m.Dot(m) - (sphereRad * sphereRad);
	// ���C�̎n�_ �� ���̊O�� (c > 0) && ���C �� �� ���痣��Ă������� (b > 0) �� ������Ȃ�
	if (c > 0.0f && b > 0.0f) { return false; }

	float discr = b * b - c;
	// �� �� ���C �� �� ���O��Ă��� �� ������Ȃ�
	if (discr < 0.0f) { return false; }

	// ����
	float ts = -b - sqrtf(discr); // �n�_
	float te = -b + sqrtf(discr); // �I�_

	// t �� �� �� ���C�̓���
	if (ts < 0) { ts = 0.0f; }
	if (te < 0) { te = 0.0f; }
	
	// ����
	distance = ts;
	//distance = te;

	// �����_
	start = rayStart + (ts * rayDirection); // �n�_
	end	  = rayStart + (te * rayDirection); // �I�_

	return true;
}

#pragma endregion


#pragma region ���ʂƋ�

bool YMath::CollisionPlaneSphere(
	const Vector3& planeNormal, const float planeDist, 
	const Vector3& sphereCenter, const float sphereRad)
{
	// ���_ �� �� �̋���
	float sphereDist = sphereCenter.Dot(planeNormal);
	
	// (�� - ����) = �� �� ���� �̋���
	float dist = sphereDist - planeDist;
	// (����(��Βl) > ���̔��a) = �������ĂȂ�
	if (fabsf(dist) > sphereRad) { return false; }

	return true;
}
bool YMath::CollisionPlaneSphere(
	const Vector3& planeNormal, const float planeDist, 
	const Vector3& sphereCenter, const float sphereRad,
	Vector3& inter)
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


#pragma region �O�p�`�Ƌ�

static YMath::Vector3 ClosestPointTriangle(const Vector3& point, const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2)
{
	// p0 �� �O�� ��
	Vector3 p0_p1 = triPos1 - triPos0;
	Vector3 p0_p2 = triPos2 - triPos0;
	Vector3 p0_pt = point - triPos0;

	float d1 = p0_p1.Dot(p0_pt);
	float d2 = p0_p2.Dot(p0_pt);

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		// p0 �� �ŋߖT
		return triPos0;
	}

	// p1 �� �O�� ��
	Vector3 p1_pt = point - triPos1;

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
	Vector3 p2_pt = point - triPos2;

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

bool YMath::CollisionTriangleSphere(
	const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal,
	const Vector3& sphereCenter, const float sphereRad)
{
	// �� �� �O�p�`�� �� �ŋߐړ_
	Vector3 closest = ClosestPointTriangle(sphereCenter, triPos0, triPos1, triPos2);
	
	// �� �� �ŋߐړ_
	Vector3 v = closest - sphereCenter;
	// (�� �� �ŋߐړ_) ^ 2 > ���̔��a ^ 2 = �������ĂȂ�
	if (v.Dot(v) > sphereRad * sphereRad) { return false; }

	return true;
}
bool YMath::CollisionTriangleSphere(
	const Vector3& triPos0, const Vector3& triPos1, const Vector3& triPos2, const Vector3& triNormal,
	const Vector3& sphereCenter, const float sphereRad, 
	Vector3& inter)
{
	// �� �� �O�p�`�� �� �ŋߐړ_
	Vector3 closest = ClosestPointTriangle(sphereCenter, triPos0, triPos1, triPos2);

	// �� �� �ŋߐړ_
	Vector3 v = closest - sphereCenter;
	// (�� �� �ŋߐړ_) ^ 2 > ���̔��a ^ 2 = �������ĂȂ�
	if (v.Dot(v) > sphereRad * sphereRad) { return false; }

	// �^����_ (�O�p�`��̍ŋߐړ_)
	inter = closest;

	return true;
}

#pragma endregion


bool YMath::CollisionSphereSphere(const Vector3& sphereCenter1, const float sphereRad1, const Vector3& sphereCenter2, const float sphereRad2)
{
	Vector3 dist = sphereCenter2 - sphereCenter1;

	if (dist.Length() > sphereRad1 + sphereRad2) { return false; }

	return false;
}