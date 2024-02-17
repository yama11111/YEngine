/**
 * @file ColorConfig.h
 * @brief 色設定
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "MathUtil.h"
#include <array>

namespace YGame
{
	namespace ColorConfig
	{
		static const std::array<YMath::Vector4, 6> skTurquoise =
		{
			YMath::GetColor(192, 252, 229, 255),
			YMath::GetColor( 19, 232, 182, 255),
			YMath::GetColor( 16, 196, 166, 255),
			YMath::GetColor(  9, 179, 150, 255),
			YMath::GetColor(  4, 142, 126, 255),
			YMath::GetColor(  3,  86,  92, 255),
		};
		
		static const YMath::Vector4 skYellow = YMath::GetColor(255, 217, 67, 255);
		
		static const YMath::Vector4 skMagenta = { 1.0f,0.0f,1.0f,1.0f };

		static const std::array<YMath::Vector4, 7> skRainbow =
		{
			YMath::GetColor(255,   0,   0, 255), // 赤
			YMath::GetColor(255, 255,   0, 255), // 黄
			YMath::GetColor(  0, 255,   0, 255), // 緑
			YMath::GetColor(  0, 255, 255, 255), // 水
			YMath::GetColor(  0,   0, 255, 255), // 青
			YMath::GetColor(255,   0, 255, 255), // 紫
			YMath::GetColor(255,   0,   0, 255), // 赤
		};
	}
}