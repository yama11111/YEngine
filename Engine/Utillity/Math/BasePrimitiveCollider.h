#pragma once
#include "Vector3.h"

namespace YMath
{
	// �_�u���f�B�X�p�b�`�p
	class RayCollider;
	class PlaneCollider;
	class TriangleCollider;
	class SphereCollider;
	class Box2DCollider;

	// �v���~�e�B�u�R���C�_�[���N���X
	class BasePrimitiveCollider
	{

	public:

		// ���蔲���t���O
		bool isSlip_ = false;

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pFollowPoint"> : �Ǐ]�_</param>
		/// <param name="offset"> : ����</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		void Initialize(Vector3* pFollowPoint, const Vector3& offset, const bool isSlip = false);

		/// <summary>
		/// �Փ˔���
		/// </summary>
		/// <param name="other"> : ����</param>
		/// <returns>�Փ˂�����</returns>
		virtual bool CheckCollision(const BasePrimitiveCollider& other) const = 0;

	public:

		/// <summary>
		// �Ǐ]�_�ݒ�
		/// </summary>
		/// <param name="pFollowPoint"> : �Ǐ]�_</param>
		inline void SetFollowPoint(Vector3* pFollowPoint) { pFollowPoint_ = pFollowPoint; }

		/// <summary>
		// ����ݒ�
		/// </summary>
		/// <param name="offset"> : ����</param>
		inline void SetOffset(const Vector3& offset) { offset_ = offset; }
	
	public:

		// ��̓I�ȏ���
		virtual bool CheckConcreteCollision(const RayCollider& other) const { return false; }
		virtual bool CheckConcreteCollision(const PlaneCollider& other) const { return false; }
		virtual bool CheckConcreteCollision(const TriangleCollider& other) const { return false; }
		virtual bool CheckConcreteCollision(const SphereCollider& other) const { return false; }
		virtual bool CheckConcreteCollision(const Box2DCollider& other) const { return false; }

	protected:

		// �Ǐ]�_
		Vector3* pFollowPoint_ = nullptr;

		// ����
		Vector3 offset_;

	public:

		BasePrimitiveCollider() = default;

		BasePrimitiveCollider(const bool isSlip);
		
		BasePrimitiveCollider(Vector3* pFollowPoint, const Vector3& offset, const bool isSlip = false);

		virtual ~BasePrimitiveCollider() = default;
	};
}

