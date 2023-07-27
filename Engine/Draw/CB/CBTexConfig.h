#pragma once
#include "Vector2.h"
#include <string>

namespace YGame
{
	// �e�N�X�`���ݒ�p�萔�o�b�t�@
	struct CBTexConfig
	{

	public:

		// �萔�o�b�t�@�f�[�^�\����
		struct Data
		{
			// �^�C�����O�l
			YMath::Vector2 tiling = { 1.0f,1.0f };

			float pad1;

			float pad2;

			// �I�t�Z�b�g�l
			YMath::Vector2 offset = { 0.0f,0.0f };
			
			float pad3;
			
			float pad4;
		};

	public:

		/// <summary>
		/// �^�O�擾
		/// </summary>
		/// <returns>�^�O��</returns>
		static const std::string Tag()
		{
			return "CBTexConfig";
		}
	};
}
