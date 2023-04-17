#pragma once
#include "ConstBuffer.h"
#include "Vector3.h"
#include "Vector4.h"

namespace YGame
{
	class Color
	{
	public:

		// �萔�o�b�t�@�f�[�^�\���� (�F)
		struct CBData
		{
			YMath::Vector4 color_; // �F (RGBA)
			YMath::Vector4 originalRate_; // ���̐F�̊���
		};

	private:

		// �F
		YMath::Vector4 color_;
		
		// ���̐F�̊���
		YMath::Vector4 originalRate_;
		
		// �萔�o�b�t�@(�}�e���A��1)
		YDX::ConstBuffer<CBData> cBuff_;

	public:

		/// <summary>
		/// ����
		/// </summary>
		/// <param name="color"> : �F</param>
		/// <param name="originalRate"> : ���̐F�̊���</param>
		/// <param name="isMutable"> : �V�[���J�ڎ��ɊJ�����邩</param>
		/// <returns></returns>
		static Color* Create(
			const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f },
			const YMath::Vector4& originalRate = { 1.0f,1.0f,1.0f,1.0f },
			const bool isMutable = true
		);

	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="color"> : �F</param>
		/// <param name="originalRate"> : ���̐F�̊���</param>
		void Initialize(
			const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f },
			const YMath::Vector4& originalRate = { 1.0f,1.0f,1.0f,1.0f }
		);

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
		YMath::Vector4 GetRGBA() const { return color_; }
		

		/// <summary>
		/// �F + �A���t�@�l�ݒ� (0.0f �` 1.0f)
		/// </summary>
		/// <param name="color"></param>
		void SetRGBA(const YMath::Vector4& color);
		
		/// <summary>
		/// �F + �A���t�@�l�ݒ� (0 �` 255)
		/// </summary>
		/// <param name="R"> : ��</param>
		/// <param name="G"> : ��</param>
		/// <param name="B"> : ��</param>
		/// <param name="A"> : �A���t�@�l</param>
		void SetRGBA(const UINT R, const UINT G, const UINT B, const UINT A);
		
		/// <summary>
		/// �F�ݒ� (0.0f �` 1.0f)
		/// </summary>
		/// <param name="color"> : RGB</param>
		void SetRGB(const YMath::Vector3& color);
		
		/// <summary>
		/// �F�ݒ� (0 �` 255)
		/// </summary>
		/// <param name="R"> : ��</param>
		/// <param name="G"> : ��</param>
		/// <param name="B"> : ��</param>
		void SetRGB(const UINT R, const UINT G, const UINT B);
		
		/// <summary>
		/// �A���t�@�l�ݒ� (0.0f �` 1.0f)
		/// </summary>
		/// <param name="alpha"> : �A���t�@�l</param>
		void SetAlpha(const float alpha);
		
		/// <summary>
		/// �A���t�@�l�ݒ� (0 �` 255)
		/// </summary>
		/// <param name="alpha"> : �A���t�@�l</param>
		void SetAlpha(const UINT alpha);

	public:
		
		/// <summary>
		/// ���̐F�̊����擾
		/// </summary>
		/// <returns>RGBA�̊���</returns>
		YMath::Vector4 GetOriginalRate() const { return originalRate_; }
		

		/// <summary>
		/// �F + �A���t�@�l�̊����ݒ� (0.0f �` 1.0f)
		/// </summary>
		/// <param name="color"> : RGBA�̊���</param>
		void SetOriginalRateRGBA(const YMath::Vector4& color);
		
		/// <summary>
		/// �F + �A���t�@�l�̊����ݒ� (0 �` 255)
		/// </summary>
		/// <param name="R"> : �Ԃ̊���</param>
		/// <param name="G"> : �΂̊���</param>
		/// <param name="B"> : �̊���</param>
		/// <param name="A"> : �A���t�@�l�̊���</param>
		void SetOriginalRateRGBA(const UINT R, const UINT G, const UINT B, const UINT A);
		
		/// <summary>
		/// �F�̊����ݒ� (0.0f �` 1.0f)
		/// </summary>
		/// <param name="color"> : RGB�̊���</param>
		void SetOriginalRateRGB(const YMath::Vector3& color);
		
		/// <summary>
		/// �F�̊����ݒ� (0 �` 255)
		/// </summary>
		/// <param name="R"> : �Ԃ̊���</param>
		/// <param name="G"> : �΂̊���</param>
		/// <param name="B"> : �̊���</param>
		void SetOriginalRateRGB(const UINT R, const UINT G, const UINT B);
		
		/// <summary>
		/// �A���t�@�l�ݒ� (0.0f �` 1.0f)
		/// </summary>
		/// <param name="alpha"> : �A���t�@�l�̊���</param>
		void SetOriginalRateAlpha(const float alpha);
		
		/// <summary>
		/// �A���t�@�l�ݒ� (0 �` 255)
		/// </summary>
		/// <param name="alpha"> : �A���t�@�l�̊���</param>
		void SetOriginalRateAlpha(const UINT alpha);

	private:

		Color();

	public:

		~Color() = default;

	};
}

