#pragma once
#include "Vector3.h"
#include <string>

namespace YGame
{
	// マテリアル用定数バッファ
	struct CBMaterial
	{

	public:

		// 定数バッファデータ構造体
		struct CBData
		{
			// アンビエント係数
			YMath::Vector3 ambient = { 1.0f,1.0f,1.0f };

			float pad1;

			// ディフューズ係数
			YMath::Vector3 diffuse = { 1.0f,1.0f,1.0f };

			float pad2;

			// スペキュラー係数
			YMath::Vector3 specular = { 1.0f,1.0f,1.0f };
			
			// アルファ値
			float alpha = 1.0f;
		};

	public:

		/// <summary>
		/// キーの名前取得
		/// </summary>
		/// <returns>キーの名前</returns>
		static const std::string KeyName()
		{
			return "CBMaterial";
		}
	};
}