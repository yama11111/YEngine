/**
 * @file CBTime.h
 * @brief 時間の定数バッファ用構造体
 * @author Yamanaka Rui
 * @date 2024/02/03
 */

#pragma once
#include <string>

namespace YGame
{
	// 時間用定数バッファ
	struct CBTime
	{

	public:

		// 定数バッファデータ構造体
		struct Data
		{
			// 時間
			float time = 0.0f;
			
			float pad1;
			
			float pad2;
			
			float pad3;
		};

	public:

		/// <summary>
		/// タグ取得
		/// </summary>
		/// <returns>タグ名</returns>
		static const std::string Tag()
		{
			return "CBTime";
		}
	};
}
