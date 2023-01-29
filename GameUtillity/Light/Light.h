#pragma once
#include "ConstBuffer.h"
#include "Vec3.h"

namespace YGame
{
	class Light
	{
	private:
		// �萔�o�b�t�@�f�[�^�\���� (��)
		struct CBData
		{
			YMath::Vec3 lightVec_;	 // ����
			float pad;				 // �p�f�B���O
			YMath::Vec3 lightColor_; // �F
		};
	private:
		// ����
		YMath::Vec3 direction_;
		// �F
		YMath::Vec3 color_;
		// �萔�o�b�t�@(��)
		YDX::ConstBuffer<CBData> cBuff_;
	public:
		// ������
		void Initialize(const YMath::Vec3& direction, const YMath::Vec3& color = { 1.0f,1.0f,1.0f });
		// �`��O�R�}���h
		void SetDrawCommand(const UINT rootParamIndex);
	public:
		// ����
		void SetDirection(const YMath::Vec3& direciton);
		// �F�ݒ� (0.0f �` 1.0f)
		void SetColor(const YMath::Vec3& color);
		// �F�ݒ� (0 �` 255)
		void SetColor(const UINT R, const UINT G, const UINT B);
	public:
		Light();
		~Light() = default;
	};
}
