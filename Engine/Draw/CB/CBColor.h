#pragma once
#include "Vector4.h"
#include <string>

namespace YGame
{
	// �F�p�萔�o�b�t�@
	struct CBColor
	{

	public:

		// �萔�o�b�t�@�f�[�^�\����
		struct Data
		{
			// �F (RGBA)
			YMath::Vector4 baseColor = { 1.0f,1.0f,1.0f,1.0f };
			
			// �e�N�X�`���̐F�̊���
			YMath::Vector4 texColorRate = { 1.0f,1.0f,1.0f,1.0f };
		};

	public:

		/// <summary>
		/// �^�O�擾
		/// </summary>
		/// <returns>�^�O��</returns>
		static const std::string Tag()
		{
			return "CBColor";
		}
	};
}
