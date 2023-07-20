#pragma once
#include "Matrix4.h"
#include <string>

namespace YGame
{
	// �X�v���C�g2D�p�萔�o�b�t�@
	struct CBSprite2DTransform
	{

	public:

		// �萔�o�b�t�@�f�[�^�\����
		struct CBData
		{
			// 3D�ϊ��s��
			YMath::Matrix4 matWorld = YMath::Matrix4::Identity();
		};

	public:

		/// <summary>
		/// �L�[�̖��O�擾
		/// </summary>
		/// <returns>�L�[�̖��O</returns>
		static const std::string KeyName()
		{
			return "CBSprite2DTransform";
		}
	};
}