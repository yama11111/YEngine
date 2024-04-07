/**
 * @file CBTexConfig.h
 * @brief テクスチャ設定用定数バッファクラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

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
		struct Data
		{
			// タイリング値
			YMath::Vector2 tiling = { 1.0f,1.0f };

			// オフセット値
			YMath::Vector2 offset = { 0.0f,0.0f };
		};

	public:

		/// <summary>
		/// タグ取得
		/// </summary>
		/// <returns>タグ名</returns>
		static const std::string Tag()
		{
			return "CBTexConfig";
		}
	};
}
