#pragma once
#include "Vector2.h"
#include "Vector3.h"

namespace YGame
{
	// ���C
	class Ray 
	{
	public:
		// �����ʒu
		YMath::Vector3 start_ = { 0,0,0 };
		// ����
		YMath::Vector3 direction_ = { 1,0,0 };
	public:
		// �����ݒ� (���K������悤��)
		void SafeSetDirection(const YMath::Vector3& direction);
	};

	// ����
	class Plane 
	{
	public:
		// �@���x�N�g��
		YMath::Vector3 normal_ = { 0.0f,+1.0f,0.0f };
		// ���_����̋���
		float distance_ = 0.0f;
	public:
		// �@���ݒ� (���K������悤��)
		void SafeSetNormal(const YMath::Vector3& normal);
	};

	// �O�p�`
	class Triangle 
	{
	public:
		// ���_���W
		YMath::Vector3 p0_;
		YMath::Vector3 p1_;
		YMath::Vector3 p2_;
		// �@���x�N�g��
		YMath::Vector3 normal_;
	public:
		// �@���ݒ� (���K������悤��)
		void SafeSetNormal(const YMath::Vector3& normal);
		// �@���̌v�Z (���݂�3�_����)
		void CalcNormal();
	};

	// ��
	class Sphere
	{
	public:
		// ���S���W
		YMath::Vector3 center_ = { 0.0f,0.0f,0.0f };
		// ���a
		float radius_ = 0.0f;
	public:
		// ���a�ݒ� (���̒l�ɂȂ�Ȃ��悤��)
		void SafeSetRadius(const float rad);
	};
	
	//     �� �~ ����
	bool CollisionRayPlane(const Ray& ray, const Plane& plane);
	
	//     �� �~ �O�p�`
	bool CollisionRayTriangle(const Ray& ray, const Triangle& triangle);

	//     �� �~ ��
	bool CollisionRaySphere(const Ray& ray, const Sphere& sphere);

	//   ���� �~ ��
	bool CollisionPlaneSphere(const Plane& plane, const Sphere& sphere);

	// �O�p�` �~ ��
	bool CollisionTriangleSphere(const Triangle& triangle, const Sphere& sphere);

	//     �� �~ ��
	bool CollisionSphereSphere(const Sphere& sphere1, const Sphere& sphere2);

}
