#pragma once
#include "Vector3.h"
#include "Vector2.h"

namespace YGame
{
	class SpotLight
	{
	public:
		// �萔�o�b�t�@�f�[�^�\���� (��)
		struct CBData
		{
			YMath::Vector3 lightPos_; // ���W
			float pad1_; // �p�f�B���O
			YMath::Vector3 lightVec_; // ����
			float pad2_; // �p�f�B���O
			YMath::Vector3 lightColor_; // �F
			float pad3_; // �p�f�B���O
			YMath::Vector3 lightAtten_; // ���������W��
			float pad4_; // �p�f�B���O
			float lightStartFactorAngleCos_; // �����J�n�p�x
			float lightEndFactorAngleCos_; // �����I���p�x
			float active_; // ����t���O
			float pad5_; // �p�f�B���O
		};
	private:
		// ���W
		YMath::Vector3 pos_;
		// ����
		YMath::Vector3 direction_;
		// �F
		YMath::Vector3 color_;
		// ���������W��
		YMath::Vector3 atten_;
		// �����J�n�p�x
		float startFactorAngleCos_ = 0.0f;
		// �����I���p�x
		float endFactorAngleCos_ = 0.0f;
		// �L���t���O
		bool isAct_ = false;
	public:
		// ������
		void Initialize(const YMath::Vector3& pos, const YMath::Vector3& direction = { 0.0f,-1.0f,0.0f },
			const YMath::Vector3& color = { 1.0f,1.0f,1.0f }, const YMath::Vector3& atten = { 0.005f,0.005f,0.005f },
			const float startFactorAngleCos = 0.5f, const float endFactorAngleCos = 0.2f);
	public:
		// ���W�擾
		YMath::Vector3 Pos() { return pos_; }
		// ���W�ݒ�
		void SetPos(const YMath::Vector3& pos);
		// �����擾
		YMath::Vector3 Direction() { return direction_; }
		// ����
		void SetDirection(const YMath::Vector3& direciton);
		// �F�擾
		YMath::Vector3 Color() { return color_; }
		// �F�ݒ� (0.0f �` 1.0f)
		void SetColor(const YMath::Vector3& color);
		// �F�ݒ� (0 �` 255)
		void SetColor(const unsigned int R, const unsigned int G, const unsigned int B);
		// ���������W���擾
		YMath::Vector3 Atten() { return atten_; }
		// ���������W���ݒ�
		void SetAtten(const YMath::Vector3& atten);
		// �����J�n�p�x�擾
		float StartFactorAngleCos() { return startFactorAngleCos_; }
		// �����J�n�p�x�ݒ�
		void SetStartFactorAngleCos(const float startFactorAngleCos);
		// �����I���p�x�擾
		float EndFactorAngleCos() { return startFactorAngleCos_; }
		// �����I���p�x�ݒ�
		void SetEndFactorAngleCos(const float endFactorAngleCos);
		// �L����
		bool IsActive() { return isAct_; }
		// �L���t���O�ݒ�
		void SetActive(const bool isAct) { isAct_ = isAct; }
	public:
		SpotLight();
		~SpotLight() = default;
	};
}
