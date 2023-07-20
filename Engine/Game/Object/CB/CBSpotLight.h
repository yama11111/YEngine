#pragma once
#include "Vector3.h"
#include <string>

namespace YGame
{
	// �X�|�b�g���C�g�萔�o�b�t�@
	struct CBSpotLight
	{

	public:

		// �萔�o�b�t�@�f�[�^�\����
		struct CBData
		{
			// ���W
			YMath::Vector3 lightPos;
			
			float pad1;
			
			// ����
			YMath::Vector3 lightVec = { 0.0f,-1.0f,0.0f };

			float pad2;

			// �F
			YMath::Vector3 lightColor = { 1.0f,1.0f,1.0f };

			float pad3;

			// ���������W��
			YMath::Vector3 lightAtten = { 0.005f,0.005f,0.005f };
			
			float pad4;
			
			// �����J�n�p�x
			float lightStartFactorAngleCos = 0.5f;

			// �����I���p�x
			float lightEndFactorAngleCos = 0.2f;
			
			// ����t���O
			float active = 0.0f;
			
			float pad5;
		};

	public:

		/// <summary>
		/// �L�[�̖��O�擾
		/// </summary>
		/// <returns>�L�[�̖��O</returns>
		static const std::string KeyName()
		{
			return "CBSpotLight";
		}
	};
}
