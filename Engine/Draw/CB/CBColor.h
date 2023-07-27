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
		struct Data
		{
			// 色 (RGBA)
			YMath::Vector4 baseColor = { 1.0f,1.0f,1.0f,1.0f };
			
			// テクスチャの色の割合
			YMath::Vector4 texColorRate = { 1.0f,1.0f,1.0f,1.0f };
		};

	public:

		/// <summary>
		/// タグ取得
		/// </summary>
		/// <returns>タグ名</returns>
		static const std::string Tag()
		{
			return "CBColor";
		}
	};
}
