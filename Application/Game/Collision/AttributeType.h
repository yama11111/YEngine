#pragma once
#include <cstdint>

namespace YGame
{
	// 属性
	enum class AttributeType : uint32_t
	{
		// 無し
		eNone			 = 0,

		// 全て
		eAll			 = 0xffffffff,

		// プレイヤー
		ePlayer			 = 0b1 << 0,
		
		// ペット
		ePet			 = 0b1 << 1,

		// プレイヤー陣営攻撃
		ePlayerAttack	 = 0b1 << 2,

		// エネミー
		eEnemy			 = 0b1 << 3,
		
		// エネミー陣営攻撃
		eEnemyAttack	 = 0b1 << 4,

		// アイテム
		eItem			 = 0b1 << 5,
		
		// ブロック
		eBlock			 = 0b1 << 6,
	};
}
