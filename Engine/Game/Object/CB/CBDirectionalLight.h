#pragma once
#include "Vector3.h"
#include <string>

namespace YGame
{
	// ���s�����萔�o�b�t�@
	struct CBDirectionalLight
	{

	public:

		// �萔�o�b�t�@�f�[�^�\����
		struct CBData
		{
			// ����
			YMath::Vector3 lightVec = { 1.0f,-1.0f,1.0f };
			
			float pad;
			
			// �F
			YMath::Vector3 lightColor = { 1.0f,1.0f,1.0f };
			
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
			return "CBDirectionalLight";
		}
	};
}