#pragma once
#include <cstdint>

namespace YGame
{
	// 属性
	namespace Attribute
	{
		// 無し
		const uint32_t None			 = 0;
		// 全て
		const uint32_t All			 = 0xffffffff;
		// プレイヤー
		const uint32_t Player		 = 0b1;
		// プレイヤーの攻撃
		const uint32_t PlayerAttack	 = 0b1 << 1;
		// エネミー
		const uint32_t Enemy		 = 0b1 << 2;
		// アイテム
		const uint32_t Item			 = 0b1 << 3;
	}
}
