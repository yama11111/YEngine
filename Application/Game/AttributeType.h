#pragma once
#include <cstdint>

namespace YGame
{
	// ����
	enum class AttributeType : uint32_t
	{
		// ����
		eNone	 = 0,

		// �S��
		eAll	 = 0xffffffff,

		// �v���C���[
		ePlayer	 = 0b1,

		// �G�l�~�[
		eEnemy	 = 0b1 << 1,

		// �A�C�e��
		eItem	 = 0b1 << 2,
	};
}
