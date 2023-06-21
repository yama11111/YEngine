#pragma once
#include "CollisionPrimitive.h"
#include <cstdint>

namespace YGame
{

	// �R���C�_�[���N���X
	class BaseCollider : 
		public Sphere
	{
	
	public:

		/// <summary>
		/// �����擾
		/// </summary>
		/// <returns>����</returns>
		inline uint32_t Attribute() const { return attribute_; }

		/// <summary>
		/// �}�X�N�擾
		/// </summary>
		/// <returns>�}�X�N</returns>
		inline uint32_t Mask() const { return mask_; }

		/// <summary>
		/// ���蔲���t���O�擾
		/// </summary>
		/// <returns>���蔲���t���O</returns>
		inline bool IsSlip() const { return isSlip_; };
	
	protected:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="attribute"> : ����</param>
		/// <param name="mask"> : �}�X�N</param>
		/// <param name="pPos"> : �ʒu�|�C���^</param>
		/// <param name="radius"> : ���a</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		void Initialize(
			const uint32_t attribute, 
			const uint32_t mask, 
			YMath::Vector3* pPos,
			const float radius,
			const bool isSlip = false);
		
		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

	protected:

		/// <summary>
		/// �����ݒ�
		/// </summary>
		/// <param name="attribute"> : ����</param>
		inline void SetAttribute(const uint32_t attribute) { attribute_ = attribute; }

		/// <summary>
		/// �}�X�N�ݒ�
		/// </summary>
		/// <param name="mask"> : �}�X�N</param>
		inline void SetMask(const uint32_t mask) { mask_ = mask; }

		/// <summary>
		/// ���蔲���t���O�ݒ�
		/// </summary>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		inline void SetIsSlip(const bool isSlip) { isSlip_ = isSlip; }

		/// <summary>
		/// �ʒu�|�C���^�ݒ�
		/// </summary>
		/// <param name="pPos"> : �ʒu�|�C���^</param>
		void SetPosPointer(YMath::Vector3* pPos);

	public:

		BaseCollider() = default;

		virtual ~BaseCollider() = default;
	
	protected:
		
		// ���� (����)
		uint32_t attribute_ = 0xffffffff;
		
		// �}�X�N (����)
		uint32_t mask_ = 0xffffffff;

		// �ʒu�|�C���^
		YMath::Vector3* pPos_ = nullptr;
		
		// ���蔲���t���O
		bool isSlip_ = false;

	};
}
