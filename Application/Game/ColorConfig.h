#pragma once
#include "MathUtil.h"
#include <array>

namespace YGame
{
	namespace ColorConfig
	{
		static const std::array<YMath::Vector4, 5> skTurquoise =
		{
			YMath::GetColor(120, 255, 205, 255),
			YMath::GetColor( 19, 232, 182, 255),
			YMath::GetColor( 16, 196, 166, 255),
			YMath::GetColor(  9, 179, 150, 255),
			YMath::GetColor(  4, 142, 126, 255),
		};
		
		static const YMath::Vector4 skYellow = YMath::GetColor(255, 217, 67, 255);
	}
}