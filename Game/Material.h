#pragma once
#include "Vec3.h"
#include <string>

namespace Game
{
	struct Material
	{
		std::string name_; // マテリアル名
		Math::Vec3 ambient_; // アンビエント影響度
		Math::Vec3 diffuse_; // ディフューズ影響度
		Math::Vec3 specular_; // スペキュラー影響度
		float alpha_; // アルファ値
		std::string textureFileName_; // テクスチャファイル名
		Material()
		{
			ambient_ = { 0.3f,0.3f,0.3f };
			diffuse_ = { 0.0f,0.0f,0.0f };
			specular_ = { 0.0f,0.0f,0.0f };
			alpha_ = 1.0f;
		}
	};
}