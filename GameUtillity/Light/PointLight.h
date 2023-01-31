#pragma once
#include "Vec3.h"

namespace YGame
{
	class PointLight
	{
	public:
		// �萔�o�b�t�@�f�[�^�\���� (��)
		struct CBData
		{
			YMath::Vec3 lightPos_; // ���W
			float pad1_; // �p�f�B���O
			YMath::Vec3 lightColor_; // �F
			float pad2_; // �p�f�B���O
			YMath::Vec3 lightAtten_; // ���������W��
			float active_; // ����t���O
		};
	private:
		// ���W
		YMath::Vec3 pos_;
		// �F
		YMath::Vec3 color_;
		// ���������W��
		YMath::Vec3 atten_;
		// �L���t���O
		bool isAct_ = false;
	public:
		// ������
		void Initialize(const YMath::Vec3& pos, const YMath::Vec3& color = { 1.0f,1.0f,1.0f }, 
			const YMath::Vec3& atten = { 0.005f,0.005f,0.005f });
	public:
		// ���W�擾
		YMath::Vec3 Pos() { return pos_; }
		// ���W�ݒ�
		void SetPos(const YMath::Vec3& pos);
		// �F�擾
		YMath::Vec3 Color() { return color_; }
		// �F�ݒ� (0.0f �` 1.0f)
		void SetColor(const YMath::Vec3& color);
		// �F�ݒ� (0 �` 255)
		void SetColor(const unsigned int R, const unsigned int G, const unsigned int B);
		// ���������W���擾
		YMath::Vec3 Atten() { return atten_; }
		// ���������W���ݒ�
		void SetAtten(const YMath::Vec3& atten);
		// �L����
		bool IsActive() { return isAct_; }
		// �L���t���O�ݒ�
		void SetActive(const bool isAct) { isAct_ = isAct; }
	public:
		PointLight();
		~PointLight() = default;
	};
}
