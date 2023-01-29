#pragma once
#include "ConstBuffer.h"
#include "Vec4.h"

namespace YGame
{
	class Color
	{
	private:
		// �萔�o�b�t�@�f�[�^�\���� (�F)
		struct CBData
		{
			YMath::Vec4 color_; // �F (RGBA)
		};
	private:
		// �F
		YMath::Vec4 color_;
		// �萔�o�b�t�@(�}�e���A��1)
		YDX::ConstBuffer<CBData> cBuff_;
	public:
		// ������
		void Initialize(const YMath::Vec4& color = { 1.0f,1.0f,1.0f,1.0f });
		// �`��O�R�}���h
		void SetDrawCommand(const UINT rootParamIndex);
	public:
		// �F�ݒ� (0.0f �` 1.0f)
		void SetRGBA(const YMath::Vec4& color);
		// �F�ݒ� (0 �` 255)
		void SetRGBA(const UINT R, const UINT G, const UINT B, const UINT A);
	public:
		Color();
		~Color() = default;
	};
}

