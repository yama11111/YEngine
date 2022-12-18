#pragma once
#include <cstdint>

namespace Collision
{
	// ‘®«
	namespace Attribute
	{
		// player
		const uint32_t Player = 0b1;
		// enemy
		const uint32_t Enemy = 0b1 << 1;
		// item
		const uint32_t Item = 0b1 << 2;
	}
}
