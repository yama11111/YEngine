#pragma once
#include <cstdint>

namespace YGame
{
	// 属性
	namespace Attribute
	{
		// 無し
		const uint32_t kNone	 = 0;
		
		// 全て
		const uint32_t kAll		 = 0xffffffff;
		
		// プレイヤー
		const uint32_t kPlayer	 = 0b1;
		
		// エネミー
		const uint32_t kEnemy	 = 0b1 << 1;
		
		// アイテム
		const uint32_t kItem	 = 0b1 << 2;
	}
}
