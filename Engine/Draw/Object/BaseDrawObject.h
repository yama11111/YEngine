#pragma once
#include "Transform.h"
#include "ConstBufferPtrSet.h"
#include "BaseGraphic.h"

namespace YGame
{
	// ���`��I�u�W�F�N�g
	class BaseDrawObject
	{

	public:
		
		// �g�����X�t�H�[��
		Transform transform_;
	
	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="status"> : �g�����X�t�H�[���X�e�[�^�X</param>
		/// <param name="isClearWhenTransition"> : �J�ڎ��N���A���邩</param>
		virtual void Initialize(
			const Transform::Status& status = Transform::Status::Default(), 
			const bool isClearWhenTransition = true) = 0;
		
		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="status"> : �g�����X�t�H�[���X�e�[�^�X</param>
		virtual void Update(const Transform::Status& status = {}) = 0;

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="shaderTag"> : �V�F�[�_�[�^�O</param>
		/// <param name="drawPriority"> : �`��D��x</param>
		void Draw(const std::string& shaderTag, const size_t drawPriority);

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="shaderTag"> : �V�F�[�_�[�^�O</param>
		/// <param name="drawPriority"> : �`��D��x</param>
		void Draw(const std::string& shaderTag, const size_t drawPriority, BaseGraphic* pGraphic);
	
	public:

		/// <summary>
		/// �y�A�����g�ݒ�
		/// </summary>
		/// <param name="pParent"> : �e�|�C���^</param>
		void SetParent(YMath::Matrix4* pParent);
		
		/// <summary>
		/// �萔�o�b�t�@�|�C���^�}�� 
		/// (������ނ̒萔�o�b�t�@�����������ւ���)
		/// </summary>
		/// <param name="pCBuff"> : �萔�o�b�t�@�|�C���^</param>
		void InsertConstBuffer(BaseConstBuffer* pCBuff);

		/// <summary>
		/// �萔�o�b�t�@�|�C���^�}�� (�f�t�H���g)
		/// (������ނ̒萔�o�b�t�@�����������ւ���)
		/// </summary>
		/// <param name="cbTag"> : �萔�o�b�t�@�^�O</param>
		void InsertDefaultConstBuffer(const std::string& cbTag);

		/// <summary>
		/// �`�悷�邩�ݒ�
		/// </summary>
		/// <param name="isVisible">�`��t���O</param>
		void SetVisible(const bool isVisible) { isVisible_ = isVisible; }
	
	public:
		
		BaseDrawObject() = default;

		virtual ~BaseDrawObject() = default;

	protected:

		// �萔�o�b�t�@�}�b�v
		ConstBufferPtrSet cbPtrSet_;

		// �O���t�B�b�N
		BaseGraphic* pGraphic_ = nullptr;

		// �`�悷�邩
		bool isVisible_ = true;
	
	protected:

		/// <summary>
		/// �O���t�B�b�N�ݒ�
		/// </summary>
		/// <param name="pGraphic"> : �O���t�B�b�N�|�C���^</param>
		void SetGraphic(BaseGraphic* pGraphic);

	};
}