#pragma once
#include "Vec3.h"
#include <string>

namespace Game
{
	struct Material
	{
		std::string name_; // �}�e���A����
		Math::Vec3 ambient_; // �A���r�G���g�e���x
		Math::Vec3 diffuse_; // �f�B�t���[�Y�e���x
		Math::Vec3 specular_; // �X�y�L�����[�e���x
		float alpha_; // �A���t�@�l
		std::string textureFileName_; // �e�N�X�`���t�@�C����
		Material()
		{
			ambient_ = { 0.3f,0.3f,0.3f };
			diffuse_ = { 0.0f,0.0f,0.0f };
			specular_ = { 0.0f,0.0f,0.0f };
			alpha_ = 1.0f;
		}
	};
}