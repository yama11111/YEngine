#pragma once
#include <cstdint>

namespace YGame
{
	// プレイヤー
	namespace PlayerAnimationConfig
	{
		// 立ち
		static const uint16_t kIdleFrame = 60;
		
		// ジャンプ
		static const uint16_t kJumpFrame = 20;

		// 着地
		static const uint16_t kLandingFrame = 20;
		
		// 攻撃
		static const uint16_t kAttackFrame = 10;

		// 被弾
		namespace Hit
		{
			static const uint16_t kFrame = 4;

			static const float kSwing = 0.2f;
		}
		
		// 死亡
		static const uint16_t kDeadFrame = 10;
	}

	// ウマ
	namespace HorseAnimationConfig
	{
		// 立ち
		static const uint16_t kIdleFrame = 60;

		// ジャンプ
		static const uint16_t kJumpFrame = 20;

		// 着地
		static const uint16_t kLandingFrame = 20;

		// 攻撃
		static const uint16_t kAttackFrame = 10;

		// 被弾
		namespace Hit
		{
			static const uint16_t kFrame = 4;

			static const float kSwing = 0.2f;
		}

		// 死亡
		static const uint16_t kDeadFrame = 10;
	}

	// スライム
	namespace SlimeAnimationConfig
	{
		// 立ち
		static const uint16_t kIdleFrame = 60;

		// ジャンプ
		static const uint16_t kJumpFrame = 20;

		// 着地
		static const uint16_t kLandingFrame = 20;

		// 被弾
		namespace Hit
		{
			static const uint16_t kFrame = 4;

			static const float kSwing = 0.2f;
		}

		// 死亡
		static const uint16_t kDeadFrame = 10;
	}
}
