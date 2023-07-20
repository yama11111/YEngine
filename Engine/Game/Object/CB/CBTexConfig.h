#pragma once
#include "Vector2.h"
#include <string>

namespace YGame
{
	// テクスチャ設定用定数バッファ
	struct CBTexConfig
	{

	public:

		// 定数バッファデータ構造体
		struct CBData
		{
			// タイリング値
			YMath::Vector2 tiling = { 1.0f,1.0f };

			float pad1;

			float pad2;

			// オフセット値
			YMath::Vector2 offset = { 0.0f,0.0f };
			
			float pad3;
			
			float pad4;
		};

	public:

		/// <summary>
		/// キーの名前取得
		/// </summary>
		/// <returns>キーの名前</returns>
		static const std::string KeyName()
		{
			return "CBTexConfig";
		}
	};
}
