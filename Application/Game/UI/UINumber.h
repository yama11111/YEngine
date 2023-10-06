#pragma once
#include "Transform.h"
#include "ViewProjection.h"
#include "BaseConstBuffer.h"

namespace YGame
{
	class UINumber
	{

	public:

		/// <summary>
		/// ���I�C���X�^���X����
		/// </summary>
		/// <param name="num"> : ��</param>
		/// <param name="maxDigits"> : �ő包��</param>
		/// <param name="interval"> : �Ԋu</param>
		/// <param name="shouldShowZero"> : �[����\�����邩</param>
		/// <param name="pParent"> : �e�s��|�C���^</param>
		/// <param name="isClearWhenTransition"> : �J�ڎ��N���A���邩</param>
		/// <returns>���I�C���X�^���X</returns>
		static UINumber* Create2D(
			const uint32_t num, 
			const size_t maxDigits, 
			const float interval,
			const bool shouldShowZero,
			YMath::Matrix4* pParent,
			const bool isClearWhenTransition = true);

		/// <summary>
		/// ���I�C���X�^���X����
		/// </summary>
		/// <param name="num"> : ��</param>
		/// <param name="maxDigits"> : �ő包��</param>
		/// <param name="interval"> : �Ԋu</param>
		/// <param name="shouldShowZero"> : �[����\�����邩</param>
		/// <param name="pParent"> : �e�s��|�C���^</param>
		/// <param name="isClearWhenTransition"> : �J�ڎ��N���A���邩</param>
		/// <returns>���I�C���X�^���X</returns>
		static UINumber* Create3D(
			const uint32_t num, 
			const size_t maxDigits, 
			const float interval,
			const bool shouldShowZero,
			YMath::Matrix4* pParent,
			const bool isXAxisBillboard, const bool isYAxisBillboard,
			ViewProjection* pVP,
			const bool isClearWhenTransition = true);

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="num"> : ��</param>
		/// <param name="maxDigits"> : �ő包��</param>
		/// <param name="shouldShowZero"> : �[����\�����邩</param>
		/// <param name="pParent"> : �e�s��|�C���^</param>
		/// <param name="isClearWhenTransition"> : �J�ڎ��N���A���邩</param>
		virtual void Initialize2D(
			const uint32_t num,
			const size_t maxDigits,
			const float interval,
			const bool shouldShowZero,
			YMath::Matrix4* pParent,
			const bool isClearWhenTransition = true) = 0;
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="num"> : ��</param>
		/// <param name="maxDigits"> : �ő包��</param>
		/// <param name="shouldShowZero"> : �[����\�����邩</param>
		/// <param name="pParent"> : �e�s��|�C���^</param>
		/// <param name="isClearWhenTransition"> : �J�ڎ��N���A���邩</param>
		virtual void Initialize3D(
			const uint32_t num,
			const size_t maxDigits,
			const float interval,
			const bool shouldShowZero,
			YMath::Matrix4* pParent,
			const bool isXAxisBillboard, const bool isYAxisBillboard,
			ViewProjection* pVP,
			const bool isClearWhenTransition = true) = 0;

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update(const Transform::Status& status = {}) = 0;

		/// <summary>
		/// �`��
		/// </summary>
		/// <param name="shaderTag"> : �V�F�[�_�[�^�O</param>
		/// <param name="priority"> : �`��D��x</param>
		virtual void Draw(const std::string& shaderTag, const uint16_t priority) = 0;

	public:

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
		/// �Ԋu�ݒ�
		/// </summary>
		/// <param name="interval"> : �Ԋu</param>
		virtual void SetInterval(const float interval) = 0;

		/// <summary>
		/// �����Ƃ̃I�t�Z�b�g�ݒ�
		/// </summary>
		/// <param name="digitIndex"> : ���ԍ�</param>
		/// <param name="offset"> : �I�t�Z�b�g�l</param>
		virtual void SetDigitOffset(const size_t digitIndex, const YMath::Vector3& offset) = 0;

		/// <summary>
		/// �[���\���ݒ�
		/// </summary>
		/// <param name="shouldShowZero"> : �[����\�����邩</param>
		virtual void SetShowZero(const bool shouldShowZero) = 0;

		/// <summary>
		/// �A�j���[�V�����X�V
		/// </summary>
		/// <param name="digitIndex"> : ���ԍ�</param>
		/// <param name="status"> : �A�j���[�V�����X�e�[�^�X</param>
		virtual void SetAnimationStatus(const size_t digitIndex, const Transform::Status& status) = 0;

	public:

		UINumber() = default;

		virtual ~UINumber() = default;

	};
}
