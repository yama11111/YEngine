#pragma once
#include "ConstBuffer.h"
#include "Vector3.h"
#include "Vector4.h"

namespace YGame
{
	class CBColor
	{
	
	public:

		// �萔�o�b�t�@�f�[�^�\���� (�F)
		struct CBData
		{
			YMath::Vector4 baseColor_; // �F (RGBA)
			YMath::Vector4 texColorRate_; // �e�N�X�`���̐F�̊���
		};
		
	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="color"> : �F</param>
		/// <param name="originalRate"> : ���̐F�̊���</param>
		/// <param name="isMutable"> : �V�[���J�ڎ��ɊJ�����邩</param>
		/// <returns>���I�C���X�^���X (new���ꂽ����)</returns>
		static CBColor* Create(
			const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f },
			const YMath::Vector4& originalRate = { 1.0f,1.0f,1.0f,1.0f },
			const bool isMutable = true);

	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="baseColor"> : �F</param>
		/// <param name="texColorRate"> : �e�N�X�`���̐F�̊���</param>
		void Initialize(
			const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f },
			const YMath::Vector4& originalRate = { 1.0f,1.0f,1.0f,1.0f });


		/// <summary>
		/// �`��O�R�}���h
		/// </summary>
		/// <param name="rootParamIndex"> : ���[�g�p�����[�^�ԍ�</param>
		void SetDrawCommand(const UINT rootParamIndex);

	public:

		/// <summary>
		/// RGBA�擾
		/// </summary>
		/// <returns>RGBA</returns>
		YMath::Vector4 GetRGBA() const { return baseColor_; }
		

		/// <summary>
		/// �F + �A���t�@�l�ݒ� (0.0f �` 1.0f)
		/// </summary>
		/// <param name="color"></param>
		void SetRGBA(const YMath::Vector4& color);
		
		/// <summary>
		/// �F�ݒ� (0.0f �` 1.0f)
		/// </summary>
		/// <param name="color"> : RGB</param>
		void SetRGB(const YMath::Vector3& color);
		
		/// <summary>
		/// �A���t�@�l�ݒ� (0.0f �` 1.0f)
		/// </summary>
		/// <param name="alpha"> : �A���t�@�l</param>
		void SetAlpha(const float alpha);

	public:
		
		/// <summary>
		/// �e�N�X�`���̐F�̊����擾
		/// </summary>
		/// <returns>RGBA�̊���</returns>
		YMath::Vector4 GetTexColorRate() const { return texColorRate_; }
		

		/// <summary>
		/// �F + �A���t�@�l�̊����ݒ� (0.0f �` 1.0f)
		/// </summary>
		/// <param name="colorRate"> : RGBA�̊���</param>
		void SetTexColorRateRGBA(const YMath::Vector4& colorRate);

		/// <summary>
		/// �F�̊����ݒ� (0.0f �` 1.0f)
		/// </summary>
		/// <param name="colorRate"> : RGB�̊���</param>
		void SetTexColorRateRGB(const YMath::Vector3& colorRate);

		/// <summary>
		/// �A���t�@�l�ݒ� (0.0f �` 1.0f)
		/// </summary>
		/// <param name="alphaRate"> : �A���t�@�l�̊���</param>
		void SetTexColorRateAlpha(const float alphaRate);

	private:

		CBColor() = default;

	public:

		~CBColor() = default;

	private:

		// �萔�o�b�t�@(�F)
		YDX::ConstBuffer<CBData> cBuff_;

		// �F
		YMath::Vector4 baseColor_ = { 1.0f,1.0f,1.0f,1.0f };
		
		// ���̐F�̊���
		YMath::Vector4 texColorRate_ = { 1.0f,1.0f,1.0f,1.0f };

	};
}

