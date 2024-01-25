/**
 * @file CBShadowGroup.h
 * @brief 影の定数バッファ用構造体
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "CBCircleShadow.h"
#include <array>

namespace YGame
{
	// 丸影用定数バッファ
	struct CBShadowGroup
	{

	public:

		// 丸影数
		static const size_t kCircleShadowNum_ = 30;
	
	public:

		// 定数バッファデータ構造体
		struct Data
		{
			// 丸影
			std::array<CBCircleShadow::Data, kCircleShadowNum_> circleShadows_;
		};

	public:

		/// <summary>
		/// タグ取得
		/// </summary>
		/// <returns>タグ名</returns>
		static const std::string Tag()
		{
			return "CBShadowGroup";
		}
	};
}
