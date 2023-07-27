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
		struct Data
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
		/// �^�O�擾
		/// </summary>
		/// <returns>�^�O��</returns>
		static const std::string Tag()
		{
			return "CBMaterial";
		}
	};
}