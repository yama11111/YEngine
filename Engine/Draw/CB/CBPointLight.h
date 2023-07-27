#pragma once
#include "Vector3.h"
#include <string>

namespace YGame
{
	// 点光源定数バッファ
	struct CBPointLight
	{

	public:

		// 定数バッファデータ構造体
		struct Data
		{
			// 座標
			YMath::Vector3 lightPos;
			
			float pad1;
			
			// 色
			YMath::Vector3 lightColor = { 1.0f,1.0f,1.0f };

			float pad2;

			// 距離減衰係数
			YMath::Vector3 lightAtten = { 0.005f,0.005f,0.005f };
			
			// 動作フラグ
			float active = 0.0f;
		};

	public:

		/// <summary>
		/// タグ取得
		/// </summary>
		/// <returns>タグ名</returns>
		static const std::string Tag()
		{
			return "CBPointLight";
		}
	};
}
