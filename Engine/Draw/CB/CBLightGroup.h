#pragma once
#include "CBDirectionalLight.h"
#include "CBPointLight.h"
#include "CBSpotLight.h"
#include <array>

namespace YGame
{
	// 光源グループ用定数バッファ
	struct CBLightGroup
	{

	public:

		// 平行光源数
		static const size_t DireLightNum_ = 3;

		// 点光源数
		static const size_t PointLightNum_ = 3;

		// スポットライト光源数
		static const size_t SpotLightNum_ = 1;

	public:

		// 定数バッファデータ構造体
		struct Data
		{
			// 環境光の色
			YMath::Vector3 ambientColor;
			
			float pad;
			
			// 平行光源
			std::array<CBDirectionalLight::Data, DireLightNum_> direLights;
			
			// 点光源
			std::array<CBPointLight::Data, PointLightNum_> pointLights;
			
			// スポットライト光源
			//std::array<CBSpotLight::Data, SpotLightNum_> spotLights;
		};

	public:

		/// <summary>
		/// タグ取得
		/// </summary>
		/// <returns>タグ名</returns>
		static const std::string Tag()
		{
			return "CBLightGroup";
		}
	};
}
