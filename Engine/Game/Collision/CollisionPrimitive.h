#pragma once
#include "Vector2.h"
#include "Vector3.h"

namespace YGame
{
	// ���C
	struct Ray 
	{
	
	private:
		
		// �����ʒu
		YMath::Vector3 start_ = { 0,0,0 };
		
		// ����
		YMath::Vector3 direction_ = { 1,0,0 };
	
	public:
		
		// ���C�J�n�ʒu�ݒ�
		void SetRayStart(const YMath::Vector3& start);

		// ���C�����ݒ�
		void SetRayDirection(const YMath::Vector3& direction);

	public:
		
		// ���C�J�n�ʒu�擾
		YMath::Vector3 GetRayStart() const { return start_; }
		
		// ���C�����擾
		YMath::Vector3 GetRayDirection() const { return direction_; }

	public:

		~Ray() = default;

	};

	// ����
	struct Plane 
	{
	
	private:
		
		// �@���x�N�g��
		YMath::Vector3 normal_ = { 0.0f,+1.0f,0.0f };
		
		// ���_����̋���
		float distance_ = 0.0f;

	public:

		// ���ʖ@���ݒ�
		void SetPlaneNormal(const YMath::Vector3& normal);
		
		// ���ʂ̌��_����̈ʒu�ݒ�
		void SetPlaneDistance(const float distance);
	
	public:

		// ���ʖ@���擾
		YMath::Vector3 GetPlaneNormal() const { return normal_; }

		// ���ʂ̌��_����̈ʒu�擾
		float GetPlaneDistance() const { return distance_; }

	public:

		~Plane() = default;

	};

	// �O�p�`
	struct Triangle 
	{
	
	private:
		
		// ���_���W
		YMath::Vector3 p0_;
		YMath::Vector3 p1_;
		YMath::Vector3 p2_;
		
		// �@���x�N�g��
		YMath::Vector3 normal_;
	
	public:
		
		// �O�p�`�ʒu�ݒ�
		void SetTrianglePos(const YMath::Vector3& p0, const YMath::Vector3& p1, const YMath::Vector3& p2);

		// �O�p�`�@���ݒ�
		void SetTriangleNormal(const YMath::Vector3& normal);
		
		// �O�p�`�@���̌v�Z (���݂�3�_����)
		void CalcTriangleNormal();

	public:

		// �O�p�`�ʒu�擾
		YMath::Vector3 GetTrianglePos(const size_t index) const;

		// �O�p�`�@���ݒ�
		YMath::Vector3 GetTriangleNormal() const { return normal_; }

	public:

		~Triangle() = default;

	};

	// ��
	struct Sphere
	{
	
	private:
		
		// ���S���W
		YMath::Vector3 center_ = { 0.0f,0.0f,0.0f };
		
		// ���a
		float radius_ = 0.0f;
	
	public:
		
		// ���̒��S���W�ݒ�
		void SetSphereCenter(const YMath::Vector3& center);

		// ���̔��a�ݒ�
		void SetSphereRadius(const float radius);

	public:

		// ���̒��S���W�擾
		YMath::Vector3 GetSphereCenter() const { return center_; }

		// ���̔��a�擾
		float GetSphereRadius() const { return radius_; }

	public:

		~Sphere() = default;
	
	};

	// �l�p�` [2D]
	struct Box2D
	{

	private:

		// ���S���W
		YMath::Vector2 center_ = { 0.0f,0.0f };

		// ���a�T�C�Y
		YMath::Vector2 radSize_ = { 0.0f,0.0f };

	public:

		// �l�p�`[2D]���S���W�ݒ�
		void SetBox2DCenter(const YMath::Vector2& center);

		// �l�p�`[2D]���a�T�C�Y�ݒ�
		void SetBox2DRadSize(const YMath::Vector2& radSize);

	public:

		// �l�p�`[2D]���S���W�ݒ�
		YMath::Vector2 GetBox2DCenter() const { return center_; }

		// �l�p�`[2D]���a�T�C�Y�ݒ�
		YMath::Vector2 GetBox2DRadSize() const { return radSize_; }

	public:

		~Box2D() = default;

	};

	
	// �� �~ ����
	bool CollisionRayPlane(const Ray& ray, const Plane& plane);
	bool CollisionRayPlane(const Ray& ray, const Plane& plane, float& distance, YMath::Vector3& inter);
	
	// �� �~ �O�p�`
	bool CollisionRayTriangle(const Ray& ray, const Triangle& triangle);

	// �� �~ ��
	bool CollisionRaySphere(const Ray& ray, const Sphere& sphere);

	// ���� �~ ��
	bool CollisionPlaneSphere(const Plane& plane, const Sphere& sphere);

	// �O�p�` �~ ��
	bool CollisionTriangleSphere(const Triangle& triangle, const Sphere& sphere);

	// �� �~ ��
	bool CollisionSphereSphere(const Sphere& sphere1, const Sphere& sphere2);


	// �l�p�`[2D] �~ �l�p�`[2D]
	bool CollisionBoxBox2D(const Box2D& box1, const Box2D& box2);

}
