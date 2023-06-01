#pragma once
#include <cstdint>

namespace YGame
{
	// ����
	namespace Attribute
	{
		// ����
		const uint32_t None			 = 0;
		// �S��
		const uint32_t All			 = 0xffffffff;
		// �v���C���[
		const uint32_t Player		 = 0b1;
		// �v���C���[�̍U��
		const uint32_t PlayerAttack	 = 0b1 << 1;
		// �G�l�~�[
		const uint32_t Enemy		 = 0b1 << 2;
		// �A�C�e��
		const uint32_t Item			 = 0b1 << 3;
	}
}
