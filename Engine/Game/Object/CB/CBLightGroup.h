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
		struct CBData
		{
			// 環境光の色
			YMath::Vector3 ambientColor;
			
			float pad;
			
			// 平行光源
			std::array<CBDirectionalLight::CBData, DireLightNum_> direLights;
			
			// 点光源
			std::array<CBPointLight::CBData, PointLightNum_> pointLights;
			
			// スポットライト光源
			//std::array<CBSpotLight::CBData, SpotLightNum_> spotLights;
		};

	public:

		/// <summary>
		/// キーの名前取得
		/// </summary>
		/// <returns>キーの名前</returns>
		static const std::string KeyName()
		{
			return "CBLightGroup";
		}
	};
}
