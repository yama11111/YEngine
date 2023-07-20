#pragma once
#include "Vector4.h"
#include <string>

namespace YGame
{
	// 色用定数バッファ
	struct CBColor
	{

	public:

		// 定数バッファデータ構造体
		struct CBData
		{
			// 色 (RGBA)
			YMath::Vector4 baseColor = { 1.0f,1.0f,1.0f,1.0f };
			
			// テクスチャの色の割合
			YMath::Vector4 texColorRate = { 1.0f,1.0f,1.0f,1.0f };
		};

	public:

		/// <summary>
		/// キーの名前取得
		/// </summary>
		/// <returns>キーの名前</returns>
		static const std::string KeyName()
		{
			return "CBColor";
		}
	};
}
