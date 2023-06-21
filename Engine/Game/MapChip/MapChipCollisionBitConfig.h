#pragma once
#include <cstdint>

namespace YGame
{
	// �}�b�v�`�b�v
	namespace ChipCollisionBit
	{
		// ����
		const uint8_t kNone	 = 0;


		// ��
		const uint8_t kTop			 = 0b00001000;
		
		// ��
		const uint8_t kBottom		 = 0b00000100;

		// ��
		const uint8_t kLeft			 = 0b00000010;

		// �E
		const uint8_t kRight		 = 0b00000001;


		// ��
		const uint8_t kElderTop		 = kTop << 4;
		
		// ��
		const uint8_t kElderBottom	 = kBottom << 4;

		// ��
		const uint8_t kElderLeft	 = kLeft << 4;

		// �E
		const uint8_t kElderRight	 = kRight << 4;
	}
}