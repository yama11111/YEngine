#pragma once
#include "Vector4.h"
#include <string>

namespace YGame
{
	// アウトライン用定数バッファ
	struct CBOutline
	{

	public:

		// 定数バッファデータ構造体
		struct Data
		{
			// 色 (RGBA)
			YMath::Vector4 color = { 1.0f,1.0f,1.0f,1.0f };

			// 範囲
			float range = 0.1f;
		};

	public:

		/// <summary>
		/// タグ取得
		/// </summary>
		/// <returns>タグ名</returns>
		static const std::string Tag()
		{
			return "CBOutline";
		}
	};
}
