#pragma once
#include <cstdint>

namespace YGame
{
	// マップチップ
	namespace ChipCollisionBit
	{
		// 無し
		const uint8_t kNone	 = 0;


		// 上
		const uint8_t kTop			 = 0b00001000;
		
		// 下
		const uint8_t kBottom		 = 0b00000100;

		// 左
		const uint8_t kLeft			 = 0b00000010;

		// 右
		const uint8_t kRight		 = 0b00000001;


		// 上
		const uint8_t kElderTop		 = kTop << 4;
		
		// 下
		const uint8_t kElderBottom	 = kBottom << 4;

		// 左
		const uint8_t kElderLeft	 = kLeft << 4;

		// 右
		const uint8_t kElderRight	 = kRight << 4;
	}
}