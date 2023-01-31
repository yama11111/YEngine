#pragma once
#include "Vec3.h"

namespace YGame
{
	class DirectionalLight
	{
	public:
		// �萔�o�b�t�@�f�[�^�\���� (��)
		struct CBData
		{
			YMath::Vec3 lightVec_; // ����
			float pad_; // �p�f�B���O
			YMath::Vec3 lightColor_; // �F
			float active_; // ����t���O
		};
	private:
		// ����
		YMath::Vec3 direction_;
		// �F
		YMath::Vec3 color_;
		// �L���t���O
		bool isAct_ = false;
	public:
		// ������
		void Initialize(const YMath::Vec3& direction, const YMath::Vec3& color = { 1.0f,1.0f,1.0f });
	public:
		// �����擾
		YMath::Vec3 Direction() { return direction_; }
		// ����
		void SetDirection(const YMath::Vec3& direciton);
		// �F�擾
		YMath::Vec3 Color() { return color_; }
		// �F�ݒ� (0.0f �` 1.0f)
		void SetColor(const YMath::Vec3& color);
		// �F�ݒ� (0 �` 255)
		void SetColor(const unsigned int R, const unsigned int G, const unsigned int B);
		// �L����
		bool IsActive() { return isAct_; }
		// �L���t���O�ݒ�
		void SetActive(const bool isAct) { isAct_ = isAct; }
	public:
		DirectionalLight();
		~DirectionalLight() = default;
	};
}

