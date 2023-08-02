#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "BasePrimitiveCollider.h"
#include <array>

namespace YMath
{
	// ���C
	class RayCollider final:
		public BasePrimitiveCollider
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="start"> ; �n�_</param>
		/// <param name="direction"> : ����</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		void Initialize(const Vector3& start, const Vector3& direction, const bool isSlip = false);

		/// <summary>
		/// ������ (�Ǐ]ver)
		/// </summary>
		/// <param name="pFollowPoint"> : �Ǐ]�_</param>
		/// <param name="offset"> : ����</param>
		/// <param name="direction"> : ����</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		void Initialize(Vector3* pFollowPoint, const Vector3& offset, const Vector3& direction, const bool isSlip = false);

		/// <summary>
		/// �Փ˔���
		/// </summary>
		/// <param name="other"> : ����</param>
		/// <returns>�Փ˂�����</returns>
		bool CheckCollision(const BasePrimitiveCollider& other) const override;

	public:

		/// <summary>
		/// �����ʒu
		/// </summary>
		/// <returns>�����ʒu</returns>
		Vector3 Start() const;

		/// <summary>
		/// ����
		/// </summary>
		/// <returns>����</returns>
		inline Vector3 Direction() const { return direction_.Normalized(); }
	
	public:

		RayCollider() = default;

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="start"> ; �n�_</param>
		/// <param name="direction"> : ����</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		RayCollider(const Vector3& start, const Vector3& direction, const bool isSlip = false);

		/// <summary>
		/// �R���X�g���N�^ (�Ǐ]ver)
		/// </summary>
		/// <param name="pFollowPoint"> : �Ǐ]�_</param>
		/// <param name="offset"> : ����</param>
		/// <param name="direction"> : ����</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		RayCollider(Vector3* pFollowPoint, const Vector3& offset, const Vector3& direction, const bool isSlip = false);

		virtual ~RayCollider() = default;

	protected:

		// �����ʒu
		Vector3 start_ = { 0,0,0 };

		// ����
		Vector3 direction_ = { 1,0,0 };

	protected:

		// �� �~ ����
		bool CheckConcreteCollision(const PlaneCollider& other) const override;

		// �� �~ �O�p�`
		bool CheckConcreteCollision(const TriangleCollider& other) const override;

		// �� �~ ��
		bool CheckConcreteCollision(const SphereCollider& other) const override;

	};

	// ����
	class PlaneCollider final:
		public BasePrimitiveCollider
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="normal"> : �@��</param>
		/// <param name="distance"> : ����</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		void Initialize(const Vector3& normal, const float distance, const bool isSlip = false);

		/// <summary>
		/// �Փ˔���
		/// </summary>
		/// <param name="other"> : ����</param>
		/// <returns>�Փ˂�����</returns>
		bool CheckCollision(const BasePrimitiveCollider& other) const override;

	public:

		/// <summary>
		/// �@��
		/// </summary>
		/// <returns>�@��</returns>
		inline Vector3 Normal() const { return normal_.Normalized(); }

		/// <summary>
		/// ����
		/// </summary>
		/// <returns>����</returns>
		inline float Distance() const { return distance_; }
	
	public:

		PlaneCollider() = default;

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="normal"> : �@��</param>
		/// <param name="distance"> : ����</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		PlaneCollider(const Vector3& normal, const float distance, const bool isSlip = false);

		virtual ~PlaneCollider() = default;

	protected:

		// �@���x�N�g��
		Vector3 normal_ = { 0.0f,+1.0f,0.0f };

		// ���_����̋���
		float distance_ = 0.0f;

	protected:

		// �� �~ ����
		bool CheckConcreteCollision(const RayCollider& other) const override;

		// ���� �~ ��
		bool CheckConcreteCollision(const SphereCollider& other) const override;
	};

	// �O�p�`
	class TriangleCollider final:
		public BasePrimitiveCollider
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="vertices"> : ���_�ʒu</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		void Initialize(const std::array<Vector3, 3>& vertices, const bool isSlip = false);

		/// <summary>
		/// ������ (�Ǐ]ver)
		/// </summary>
		/// <param name="pFollowPoint"> : �Ǐ]�_</param>
		/// <param name="offset"> : ����</param>
		/// <param name="vertices"> : ���_�ʒu</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		void Initialize(Vector3* pFollowPoint, const Vector3& offset, const std::array<Vector3, 3>& vertices, const bool isSlip = false);

		/// <summary>
		/// �O�p�`�@���̌v�Z (���݂�3�_����)
		/// </summary>
		void CalcTriangleNormal();

		/// <summary>
		/// �Փ˔���
		/// </summary>
		/// <param name="other"> : ����</param>
		/// <returns>�Փ˂�����</returns>
		bool CheckCollision(const BasePrimitiveCollider& other) const override;

	public:

		
		/// <summary>
		/// �O�p�`���_�ʒu
		/// </summary>
		/// <param name="index">�C���f�b�N�X</param>
		/// <returns>�O�p�`���_�ʒu</returns>
		YMath::Vector3 VertexPos(const size_t index) const;
		
		/// <summary>
		/// �@��
		/// </summary>
		/// <returns>�@��</returns>
		inline YMath::Vector3 Normal() const { return normal_; }

	public:

		TriangleCollider() = default;

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="vertices"> : ���_�ʒu</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		TriangleCollider(const std::array<Vector3, 3>& vertices, const bool isSlip = false);

		/// <summary>
		/// �R���X�g���N�^ (�Ǐ]ver)
		/// </summary>
		/// <param name="pFollowPoint"> : �Ǐ]�_</param>
		/// <param name="offset"> : ����</param>
		/// <param name="vertices"> : ���_�ʒu</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		TriangleCollider(Vector3* pFollowPoint, const Vector3& offset, const std::array<Vector3, 3>& vertices, const bool isSlip = false);

		virtual ~TriangleCollider() = default;

	protected:

		// ���_���W
		std::array<Vector3, 3> vertices_;

		// �@���x�N�g��
		Vector3 normal_;

	protected:

		// �� �~ �O�p�`
		bool CheckConcreteCollision(const RayCollider& other) const override;

		// �O�p�` �~ ��
		bool CheckConcreteCollision(const SphereCollider& other) const override;

	};

	// ��
	class SphereCollider final:
		public BasePrimitiveCollider
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="center"> : ���S�_</param>
		/// <param name="radius"> : ���a</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		void Initialize(const Vector3& center, const float radius, const bool isSlip = false);

		/// <summary>
		/// ������ (�Ǐ]ver)
		/// </summary>
		/// <param name="pFollowPoint"> : �Ǐ]�_</param>
		/// <param name="offset"> : ����</param>
		/// <param name="radius"> : ���a</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		void Initialize(Vector3* pFollowPoint, const Vector3& offset, const float radius, const bool isSlip = false);
		
		/// <summary>
		/// �Փ˔���
		/// </summary>
		/// <param name="other"> : ����</param>
		/// <returns>�Փ˂�����</returns>
		bool CheckCollision(const BasePrimitiveCollider& other) const override;

	public:

		/// <summary>
		/// ���S�_
		/// </summary>
		/// <returns>���S�_</returns>
		YMath::Vector3 Center() const;
		
		/// <summary>
		/// ���a
		/// </summary>
		/// <returns>���a</returns>
		inline float Radius() const { return radius_; }

	public:

		SphereCollider() = default;

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="center"> : ���S�_</param>
		/// <param name="radius"> : ���a</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		SphereCollider(const Vector3& center, const float radius, const bool isSlip = false);

		/// <summary>
		/// �R���X�g���N�^ (�Ǐ]ver)
		/// </summary>
		/// <param name="pFollowPoint"> : �Ǐ]�_</param>
		/// <param name="offset"> : ����</param>
		/// <param name="radius"> : ���a</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		SphereCollider(Vector3* pFollowPoint, const Vector3& offset, const float radius, const bool isSlip = false);


		virtual ~SphereCollider() = default;

	protected:

		// ���S�_
		YMath::Vector3 center_ = { 0.0f,0.0f,0.0f };

		// ���a
		float radius_ = 0.0f;

	protected:

		// �� �~ ��
		bool CheckConcreteCollision(const RayCollider& other) const override;

		// ���� �~ ��
		bool CheckConcreteCollision(const PlaneCollider& other) const override;

		// �O�p�` �~ ��
		bool CheckConcreteCollision(const TriangleCollider& other) const override;

		// �� �~ ��
		bool CheckConcreteCollision(const SphereCollider& other) const override;

	};

	// �l�p�` [2D]
	class Box2DCollider final:
		public BasePrimitiveCollider
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="center"> : ���S�_</param>
		/// <param name="radSize"> : ���a</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		void Initialize(const Vector2& center, const Vector2& radSize, const bool isSlip = false);
		
		/// <summary>
		/// ������ (�Ǐ]ver)
		/// </summary>
		/// <param name="pFollowPoint"> : �Ǐ]�_</param>
		/// <param name="offset"> : ����</param>
		/// <param name="radSize"> : ���a</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		void Initialize(Vector3* pFollowPoint, const Vector3& offset, const Vector2& radSize, const bool isSlip = false);

		/// <summary>
		/// �Փ˔���
		/// </summary>
		/// <param name="other"> : ����</param>
		/// <returns>�Փ˂�����</returns>
		bool CheckCollision(const BasePrimitiveCollider& other) const override;

	public:
		
		/// <summary>
		/// ���S���W
		/// </summary>
		/// <returns></returns>
		YMath::Vector2 Center() const;
		
		/// <summary>
		/// ���a
		/// </summary>
		/// <returns>���a</returns>
		inline YMath::Vector2 RadSize() const { return radSize_; }

	public:

		Box2DCollider() = default;

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="center"> : ���S�_</param>
		/// <param name="radSize"> : ���a</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		Box2DCollider(const Vector2& center, const Vector2& radSize, const bool isSlip = false);
		
		/// <summary>
		/// �R���X�g���N�^ (�Ǐ]ver)
		/// </summary>
		/// <param name="pFollowPoint"> : �Ǐ]�_</param>
		/// <param name="offset"> : ����</param>
		/// <param name="radSize"> : ���a</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		Box2DCollider(Vector3* pFollowPoint, const Vector3& offset, const Vector2& radSize, const bool isSlip = false);

		virtual ~Box2DCollider() = default;

	protected:

		// ���S���W
		YMath::Vector2 center_ = { 0.0f,0.0f };

		// ���a
		YMath::Vector2 radSize_ = { 0.0f,0.0f };

	protected:

		// �l�p�`[2D] �~ �l�p�`[2D]
		bool CheckConcreteCollision(const Box2DCollider& other) const override;

	};


	// �� �~ ����
	static bool CollisionRayPlane(const RayCollider& ray, const PlaneCollider& plane);
	static bool CollisionRayPlane(const RayCollider& ray, const PlaneCollider& plane, float& distance, YMath::Vector3& inter);

	// �� �~ �O�p�`
	static bool CollisionRayTriangle(const RayCollider& ray, const TriangleCollider& triangle);

	// �� �~ ��
	static bool CollisionRaySphere(const RayCollider& ray, const SphereCollider& sphere);

	// ���� �~ ��
	static bool CollisionPlaneSphere(const PlaneCollider& plane, const SphereCollider& sphere);

	// �O�p�` �~ ��
	static bool CollisionTriangleSphere(const TriangleCollider& triangle, const SphereCollider& sphere);

	// �� �~ ��
	static bool CollisionSphereSphere(const SphereCollider& sphere1, const SphereCollider& sphere2);

	// �l�p�`[2D] �~ �l�p�`[2D]
	static bool CollisionBoxBox2D(const Box2DCollider& box1, const Box2DCollider& box2);

}
