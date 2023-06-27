#pragma once
#include "Transform.h"
#include <cstdint>

namespace YGame
{
	// �R���C�_�[���N���X
	class BaseCollider
	{

	public:

		// �`��
		enum class ShapeType
		{
			// ���ݒ�
			eUnkown = -1,

			// ��
			eSphere,
		};
	
	public:

		/// <summary>
		/// ������ (�e�|�C���^����)
		/// </summary>
		/// <param name="offset"> : �I�t�Z�b�g</param>
		/// <param name="attribute"> : ����</param>
		/// <param name="mask"> : �}�X�N</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		void Initialize(
			const YMath::Vector3& offset,
			const uint32_t attribute, const uint32_t mask,
			const bool isSlip = false);

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pParent"> : �e�g�����X�t�H�[���|�C���^</param>
		/// <param name="offset"> : �I�t�Z�b�g</param>
		/// <param name="attribute"> : ����</param>
		/// <param name="mask"> : �}�X�N</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		void Initialize(
			Transform* pParent, const YMath::Vector3& offset,
			const uint32_t attribute, const uint32_t mask,
			const bool isSlip = false);

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update() = 0;

	public:

		/// <summary>
		/// �`��擾
		/// </summary>
		/// <returns>�`��</returns>
		inline ShapeType Shape() const { return shapeType_; }
		
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

	public:

		/// <summary>
		/// �e�g�����X�t�H�[���ݒ�
		/// </summary>
		/// <param name="pParent"> : �e�g�����X�t�H�[���|�C���^</param>
		void SetParent(Transform* pParent);

		/// <summary>
		/// �I�t�Z�b�g(����)�ݒ�
		/// </summary>
		/// <param name="offset">�I�t�Z�b�g(����)</param>
		inline void SetOffset(const YMath::Vector3& offset) { offset_ = offset; }

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

	public:

		BaseCollider() = default;
		
		/// <summary>
		/// �R���X�g���N�^ (�e�|�C���^����)
		/// </summary>
		/// <param name="offset"> : �I�t�Z�b�g</param>
		/// <param name="attribute"> : ����</param>
		/// <param name="mask"> : �}�X�N</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		BaseCollider(
			const YMath::Vector3& offset,
			const uint32_t attribute, const uint32_t mask,
			const bool isSlip = false);

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="pParent"> : �e�g�����X�t�H�[���|�C���^</param>
		/// <param name="offset"> : �I�t�Z�b�g</param>
		/// <param name="attribute"> : ����</param>
		/// <param name="mask"> : �}�X�N</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		BaseCollider(
			Transform* pParent, const YMath::Vector3& offset,
			const uint32_t attribute, const uint32_t mask,
			const bool isSlip = false);

		virtual ~BaseCollider() = default;
	
	protected:

		// �e�g�����X�t�H�[���|�C���^
		Transform* pParent_ = nullptr;

		// ����
		YMath::Vector3 offset_;

		// �`��
		ShapeType shapeType_ = ShapeType::eUnkown;
		
		// ���� (����)
		uint32_t attribute_ = 0xffffffff;
		
		// �}�X�N (����)
		uint32_t mask_ = 0xffffffff;

		// ���蔲���t���O
		bool isSlip_ = false;
	};
}
