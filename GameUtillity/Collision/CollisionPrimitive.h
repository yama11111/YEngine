#pragma once
#include "Vec2.h"
#include "Vec3.h"

namespace YCollision
{
	// ����
	class Plane 
	{
	public:
		// �@���x�N�g��
		YMath::Vec3 normal_ = { 0.0f,+1.0f,0.0f };
		// ���_����̋���
		float distance_ = 0.0f;
	public:
		void SafeSetNormal(const YMath::Vec3& normal);
	};

	// �O�p�`
	class Triangle 
	{
	public:
		// ���_���W
		YMath::Vec3 p0_;
		YMath::Vec3 p1_;
		YMath::Vec3 p2_;
		// �@���x�N�g��
		YMath::Vec3 normal_;
	public:
		void SafeSetNormal(const YMath::Vec3& normal);
	};

	// ��
	class Sphere
	{
	public:
		// ���S���W
		YMath::Vec3 center_ = { 0.0f,0.0f,0.0f };
		// ���a
		float radius_ = 0.0f;
	public:
		void SafeSetRadius(const float rad);
	};
	
	// ���� �~ ��
	bool CollisonPlaneSphere(const Plane& plane, const Sphere& sphere);

	// �O�p�` �~ ��
	bool CollisionTriangleSphere(const Triangle& triangle, const Sphere& sphere);
}
