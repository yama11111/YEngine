#pragma once
#include "Vector3.h"
#include <string>

namespace YGame
{
	// スポットライト定数バッファ
	struct CBSpotLight
	{

	public:

		// 定数バッファデータ構造体
		struct Data
		{
			// 座標
			YMath::Vector3 lightPos;
			
			float pad1;
			
			// 向き
			YMath::Vector3 lightVec = { 0.0f,-1.0f,0.0f };

			float pad2;

			// 色
			YMath::Vector3 lightColor = { 1.0f,1.0f,1.0f };

			float pad3;

			// 距離減衰係数
			YMath::Vector3 lightAtten = { 0.005f,0.005f,0.005f };
			
			float pad4;
			
			// 減衰開始角度
			float lightStartFactorAngleCos = 0.5f;

			// 減衰終了角度
			float lightEndFactorAngleCos = 0.2f;
			
			// 動作フラグ
			float active = 0.0f;
			
			float pad5;
		};

	public:

		/// <summary>
		/// タグ取得
		/// </summary>
		/// <returns>タグ名</returns>
		static const std::string Tag()
		{
			return "CBSpotLight";
		}
	};
}
