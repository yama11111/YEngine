#pragma once
#include "Vector3.h"
#include <string>

namespace YGame
{
	// �_�����萔�o�b�t�@
	struct CBPointLight
	{

	public:

		// �萔�o�b�t�@�f�[�^�\����
		struct CBData
		{
			// ���W
			YMath::Vector3 lightPos;
			
			float pad1;
			
			// �F
			YMath::Vector3 lightColor = { 1.0f,1.0f,1.0f };

			float pad2;

			// ���������W��
			YMath::Vector3 lightAtten = { 0.005f,0.005f,0.005f };
			
			// ����t���O
			float active = 0.0f;
		};

	public:

		/// <summary>
		/// �L�[�̖��O�擾
		/// </summary>
		/// <returns>�L�[�̖��O</returns>
		static const std::string KeyName()
		{
			return "CBPointLight";
		}
	};
}
