#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include "BaseConstBuffer.h"

namespace YGame
{
	class UIDigit
	{

	public:

		/// <summary>
		/// ���I�C���X�^���X����
		/// </summary>
		/// <param name="num"> : ��</param>
		/// <param name="pParent"> : �e�s��|�C���^</param>
		/// <param name="offset"> : �I�t�Z�b�g�l</param>
		/// <param name="isClearWhenTransition"> : �J�ڎ��N���A���邩</param>
		/// <returns>���I�C���X�^���X</returns>
		static UIDigit* Create(
			const uint32_t num, 
			YMath::Matrix4* pParent, 
			const YMath::Vector3& offset ={},
			const bool isClearWhenTransition = true);

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="num"> : ��</param>
		/// <param name="pParent"> : �e�s��|�C���^</param>
		/// <param name="offset"> : �I�t�Z�b�g�l</param>
		/// <param name="isClearWhenTransition"> : �J�ڎ��N���A���邩</param>
		virtual void Initialize(
			const uint32_t num, 
			YMath::Matrix4* pParent, 
			const YMath::Vector3& offset = {},
			const bool isClearWhenTransition = true) = 0;

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="shaderTag"> : �V�F�[�_�[�^�O</param>
		/// <param name="priority"> : �`��D��x</param>
		virtual void Draw(const std::string& shaderTag, const uint16_t priority) = 0;

		/// <summary>
		/// �萔�o�b�t�@�|�C���^�}�� 
		/// (������ނ̒萔�o�b�t�@�����������ւ���)
		/// </summary>
		/// <param name="pCBuff"> : �萔�o�b�t�@�|�C���^</param>
		virtual void InsertConstBuffer(BaseConstBuffer* pCB) = 0;

		/// <summary>
		/// �����ݒ�
		/// </summary>
		/// <param name="num"> : ����</param>
		virtual void SetNumber(const uint32_t num) = 0;

		/// <summary>
		/// �I�t�Z�b�g�ݒ�
		/// </summary>
		/// <param name="offset"> : �I�t�Z�b�g�l</param>
		virtual void SetOffset(const YMath::Vector3& offset) = 0;

	public:

		/// <summary>
		/// �ÓI������
		/// </summary>
		static void StaticInitialize();
		
		/// <summary>
		/// �����̕��擾
		/// </summary>
		/// <returns>�����̕�</returns>
		static const float StaticDigitWidth();
	
	public:

		UIDigit() = default;

		virtual ~UIDigit() = default;

	};
}
