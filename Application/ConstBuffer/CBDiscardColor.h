/**
 * @file CBDiscardColor.h
 * @brief 丸影の定数バッファ用構造体
 * @author Yamanaka Rui
 * @date 2024/02/03
 */

#pragma once
#include "Vector3.h"
#include <string>

namespace YGame
{
	// 消去色用定数バッファ
	struct CBDiscardColor
	{

	public:

		// 定数バッファデータ構造体
		struct Data
		{
			// 消去色
			YMath::Vector3 discardColor = { 1.0f, 0.0f, 1.0f };

			// 閾値
			float threshold = 0.2f;
		};

	public:

		/// <summary>
		/// タグ取得
		/// </summary>
		/// <returns>タグ名</returns>
		static const std::string Tag()
		{
			return "CBDiscardColor";
		}
	};
}
