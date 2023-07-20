#pragma once
#include "Vector3.h"
#include <string>

namespace YGame
{
	// �}�e���A���p�萔�o�b�t�@
	struct CBMaterial
	{

	public:

		// �萔�o�b�t�@�f�[�^�\����
		struct CBData
		{
			// �A���r�G���g�W��
			YMath::Vector3 ambient = { 1.0f,1.0f,1.0f };

			float pad1;

			// �f�B�t���[�Y�W��
			YMath::Vector3 diffuse = { 1.0f,1.0f,1.0f };

			float pad2;

			// �X�y�L�����[�W��
			YMath::Vector3 specular = { 1.0f,1.0f,1.0f };
			
			// �A���t�@�l
			float alpha = 1.0f;
		};

	public:

		/// <summary>
		/// �L�[�̖��O�擾
		/// </summary>
		/// <returns>�L�[�̖��O</returns>
		static const std::string KeyName()
		{
			return "CBMaterial";
		}
	};
}