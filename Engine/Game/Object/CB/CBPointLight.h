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
		struct CBData
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
		/// キーの名前取得
		/// </summary>
		/// <returns>キーの名前</returns>
		static const std::string KeyName()
		{
			return "CBPointLight";
		}
	};
}
