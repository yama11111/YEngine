#pragma once
#include <cstdint>

namespace YGame
{
	// ����
	namespace Attribute
	{
		// ����
		const uint32_t kNone	 = 0;
		
		// �S��
		const uint32_t kAll		 = 0xffffffff;
		
		// �v���C���[
		const uint32_t kPlayer	 = 0b1;
		
		// �G�l�~�[
		const uint32_t kEnemy	 = 0b1 << 1;
		
		// �A�C�e��
		const uint32_t kItem	 = 0b1 << 2;
	}
}
