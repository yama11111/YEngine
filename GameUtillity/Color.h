#pragma once
#include "ConstBuffer.h"
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
		};
	private:
		// �F
		YMath::Vector4 color_;
		// �萔�o�b�t�@(�}�e���A��1)
		YDX::ConstBuffer<CBData> cBuff_;
	public:
		// ����
		static Color* Create(const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f });
	public:
		// ������
		void Initialize(const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f });
		// �`��O�R�}���h
		void SetDrawCommand(const UINT rootParamIndex);
	public:
		// RGBA�擾
		YMath::Vector4 GetRGBA() const { return color_; }
		// �F�ݒ� (0.0f �` 1.0f)
		void SetRGBA(const YMath::Vector4& color);
		// �F�ݒ� (0 �` 255)
		void SetRGBA(const UINT R, const UINT G, const UINT B, const UINT A);
	private:
		Color();
	public:
		~Color() = default;
	};
}

