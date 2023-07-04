#pragma once
#include <cstdint>

namespace YGame
{
	// �v���C���[
	namespace PlayerAnimationConfig
	{
		// ����
		static const uint16_t kIdleFrame = 60;
		
		// �W�����v
		static const uint16_t kJumpFrame = 20;

		// ���n
		static const uint16_t kLandingFrame = 20;
		
		// �U��
		static const uint16_t kAttackFrame = 10;

		// ��e
		namespace Hit
		{
			static const uint16_t kFrame = 4;

			static const float kSwing = 0.2f;
		}
		
		// ���S
		static const uint16_t kDeadFrame = 10;
	}

	// �E�}
	namespace HorseAnimationConfig
	{
		// ����
		static const uint16_t kIdleFrame = 60;

		// �W�����v
		static const uint16_t kJumpFrame = 20;

		// ���n
		static const uint16_t kLandingFrame = 20;

		// �U��
		static const uint16_t kAttackFrame = 10;

		// ��e
		namespace Hit
		{
			static const uint16_t kFrame = 4;

			static const float kSwing = 0.2f;
		}

		// ���S
		static const uint16_t kDeadFrame = 10;
	}

	// �X���C��
	namespace SlimeAnimationConfig
	{
		// ����
		static const uint16_t kIdleFrame = 60;

		// �W�����v
		static const uint16_t kJumpFrame = 20;

		// ���n
		static const uint16_t kLandingFrame = 20;

		// ��e
		namespace Hit
		{
			static const uint16_t kFrame = 4;

			static const float kSwing = 0.2f;
		}

		// ���S
		static const uint16_t kDeadFrame = 10;
	}
}
