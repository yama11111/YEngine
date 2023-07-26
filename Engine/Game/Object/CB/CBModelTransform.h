#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include <string>

namespace YGame
{
	// ���f���p�萔�o�b�t�@
	struct CBModelTransform
	{

	public:

		// �萔�o�b�t�@�f�[�^�\����
		struct Data
		{
			// ���[���h�s��
			YMath::Matrix4 matWorld = YMath::Matrix4::Identity();
			
			// �r���[�v���W�F�N�V�����s��
			YMath::Matrix4 matViewProj = YMath::Matrix4::Identity();
			
			// �J�������W
			YMath::Vector3 cameraPos{};
			
			float pad;
		};

	public:

		/// <summary>
		/// �L�[�̖��O�擾
		/// </summary>
		/// <returns>�L�[�̖��O</returns>
		static const std::string TypeName()
		{
			return "CBModelTransform";
		}
	};
}
