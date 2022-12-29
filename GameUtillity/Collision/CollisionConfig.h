#pragma once
#include <cstdint>

namespace YCollision
{
	// 属性
	namespace Attribute
	{
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
