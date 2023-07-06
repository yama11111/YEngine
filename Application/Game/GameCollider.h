#pragma once
#include "AttributeType.h"
#include "Transform.h"
#include "BasePrimitiveCollider.h"
#include "DebugTextAttacher.h"
#include <list>
#include <memory>
#include <cstdint>

namespace YGame
{
	// �Q�[���p�R���C�_�[�N���X
	class GameCollider : 
		public DebugTextAttacher
	{

	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		/// <param name="attribute"> : ����</param>
		/// <param name="mask"> : �}�X�N</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		/// <param name="isClear"> : ���X�g���N���A���邩</param>
		void Initialize(
			Transform* pParent, 
			const AttributeType attribute, const AttributeType mask, 
			const bool isSlip = false,
			const bool isClear = false);

		/// <summary>
		/// �Փ˔���
		/// </summary>
		/// <param name="pOther">����|�C���^</param>
		bool CheckCollision(GameCollider* pOther);

		/// <summary>
		/// �R���C�_�[�}��
		/// </summary>
		/// <param name="collider">�R���C�_�[ (���I�C���X�^���X)</param>
		void PushBack(YMath::BasePrimitiveCollider* collider);

		/// <summary>
		/// �f�o�b�O�e�L�X�g�{��
		/// </summary>
		virtual void DrawDebugTextContent() override;

	public:

		/// <summary>
		/// �R���C�_�[���X�g�擾
		/// </summary>
		/// <returns>�R���C�_�[���X�g</returns>
		inline const std::list<std::unique_ptr<YMath::BasePrimitiveCollider>>& Colliders() const { return colliders_; }

		/// <summary>
		/// �����擾
		/// </summary>
		/// <returns>����</returns>
		inline AttributeType Attribute() const { return attribute_; }

		/// <summary>
		/// �}�X�N�擾
		/// </summary>
		/// <returns>�}�X�N</returns>
		inline AttributeType Mask() const { return mask_; }

		/// <summary>
		/// ���蔲���t���O�擾
		/// </summary>
		/// <returns>���蔲���t���O</returns>
		inline  bool IsSlip() const { return isSlip_; }
	
	public:

		/// <summary>
		/// �e�|�C���^�ݒ�
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		inline void SetParent(Transform* pParent) { pParent_ = pParent; }

		/// <summary>
		/// ���蔲���t���O�ݒ�
		/// </summary>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		inline void SetIsSlip(const bool isSlip) { isSlip_ = isSlip; }

	public:

		GameCollider() = default;

		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		/// <param name="attribute"> : ����</param>
		/// <param name="mask"> : �}�X�N</param>
		/// <param name="isSlip"> : ���蔲���t���O</param>
		GameCollider(
			Transform* pParent, 
			const AttributeType attribute, const AttributeType mask,
			const bool isSlip = false);

		virtual ~GameCollider() = default;

	private:

		// �e�|�C���^
		Transform* pParent_ = nullptr;

		// ���� (����)
		AttributeType attribute_ = AttributeType::eAll;

		// �}�X�N (����)
		AttributeType mask_ = AttributeType::eAll;

		// ���蔲���t���O
		bool isSlip_ = false;

		// �v���~�e�B�u�R���C�_�[���X�g
		std::list<std::unique_ptr<YMath::BasePrimitiveCollider>> colliders_;
	};
}
