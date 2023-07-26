#pragma once
#include "Matrix4.h"
#include <string>

namespace YGame
{
	// �|�X�g�G�t�F�N�g�p�萔�o�b�t�@
	struct CBPostEffectTransform
	{

	public:

		// �萔�o�b�t�@�f�[�^�\����
		struct Data
		{
			// 3D�ϊ��s��
			YMath::Matrix4 matWorld = YMath::Matrix4::Identity();
		};

	public:

		/// <summary>
		/// �L�[�̖��O�擾
		/// </summary>
		/// <returns>�L�[�̖��O</returns>
		static const std::string TypeName()
		{
			return "CBPostEffectTransform";
		}
	};
}