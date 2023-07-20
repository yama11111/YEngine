#pragma once
#include "CBDirectionalLight.h"
#include "CBPointLight.h"
#include "CBSpotLight.h"
#include <array>

namespace YGame
{
	// �����O���[�v�p�萔�o�b�t�@
	struct CBLightGroup
	{

	public:

		// ���s������
		static const size_t DireLightNum_ = 3;

		// �_������
		static const size_t PointLightNum_ = 3;

		// �X�|�b�g���C�g������
		static const size_t SpotLightNum_ = 1;

	public:

		// �萔�o�b�t�@�f�[�^�\����
		struct CBData
		{
			// �����̐F
			YMath::Vector3 ambientColor;
			
			float pad;
			
			// ���s����
			std::array<CBDirectionalLight::CBData, DireLightNum_> direLights;
			
			// �_����
			std::array<CBPointLight::CBData, PointLightNum_> pointLights;
			
			// �X�|�b�g���C�g����
			//std::array<CBSpotLight::CBData, SpotLightNum_> spotLights;
		};

	public:

		/// <summary>
		/// �L�[�̖��O�擾
		/// </summary>
		/// <returns>�L�[�̖��O</returns>
		static const std::string KeyName()
		{
			return "CBLightGroup";
		}
	};
}
