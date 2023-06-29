#pragma once
#include <cstdint>

namespace YGame
{
	// 属性
	enum class AttributeType : uint32_t
	{
		// 無し
		eNone	 = 0,

		// 全て
		eAll	 = 0xffffffff,

		// プレイヤー
		ePlayer	 = 0b1,

		// エネミー
		eEnemy	 = 0b1 << 1,

		// アイテム
		eItem	 = 0b1 << 2,
	};
}
