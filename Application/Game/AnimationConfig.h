#pragma once
#include <cstdint>

namespace YGame
{
	// �v���C���[
	namespace PlayerAnimationConfig
	{
		// ����
		static const uint16_t kIdleFrame = 60;

		// �ړ�
		namespace Move
		{
			static const uint16_t kFrame = 8;

			static const size_t kDustNum = 4;
		}
		
		// �W�����v
		namespace Jump
		{
			static const uint16_t kFrame = 20;
			
			static const size_t kDustNum = 8;
		}

		// ���n
		namespace Landing
		{
			static const uint16_t kFrame = 20;

			static const size_t kDirectionNum = 8;
			
			static const size_t kDustNum = 2;
		}
		
		// �U��
		static const uint16_t kAttackFrame = 10;

		// ��e
		namespace Hit
		{
			static const uint16_t kFrame = 4;

			// �u��
			static const float kSwing = 0.2f;
		}
		
		// ���S
		namespace Dead
		{
			static const uint16_t kFrame = 10;

			static const size_t kDebriNum = 16;
		}
	}

	// �E�}
	namespace HorseAnimationConfig
	{
		// ����
		static const uint16_t kIdleFrame = 60;

		// �ړ�
		namespace Move
		{
			static const uint16_t kFrame = 8;

			static const size_t kDustNum = 4;
		}

		// �W�����v
		namespace Jump
		{
			static const uint16_t kFrame = 20;

			static const size_t kDustNum = 8;
		}

		// ���n
		namespace Landing
		{
			static const uint16_t kFrame = 20;

			static const size_t kDirectionNum = 8;

			static const size_t kDustNum = 2;
		}

		// �U��
		static const uint16_t kAttackFrame = 10;

		// ��e
		namespace Hit
		{
			static const uint16_t kFrame = 4;

			// �u��
			static const float kSwing = 0.2f;
		}

		// ���S
		namespace Dead
		{
			static const uint16_t kFrame = 10;

			static const size_t kDebriNum = 16;
		}
	}

	// �X���C��
	namespace SlimeAnimationConfig
	{
		// ����
		static const uint16_t kIdleFrame = 60;

		// ���n
		namespace Landing
		{
			static const uint16_t kFrame = 20;

			static const size_t kDirectionNum = 4;

			static const size_t kDustNum = 2;
		}

		// ��e
		namespace Hit
		{
			static const uint16_t kFrame = 4;

			// �u��
			static const float kSwing = 0.2f;
		}

		// ���S
		namespace Dead
		{
			static const uint16_t kFrame = 10;

			static const size_t kDebriNum = 16;
		}
	}
}
