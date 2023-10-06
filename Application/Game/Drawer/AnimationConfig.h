#pragma once
#include <cstdint>

namespace YGame
{
	// プレイヤー
	namespace PlayerAnimationConfig
	{
		// 立ち
		static const uint16_t kIdleFrame = 60;

		// 移動
		namespace Move
		{
			static const uint16_t kFrame = 8;

			static const size_t kDustNum = 4;
		}
		
		// ジャンプ
		namespace Jump
		{
			static const uint16_t kFrame = 20;
			
			static const size_t kDustNum = 8;
		}

		// 着地
		namespace Landing
		{
			static const uint16_t kFrame = 20;

			static const size_t kDirectionNum = 8;
			
			static const size_t kDustNum = 2;
		}
		
		// 攻撃
		static const uint16_t kAttackFrame = 10;

		// 被弾
		namespace Hit
		{
			static const uint16_t kFrame = 4;

			// ブレ
			static const float kSwing = 0.2f;
		}
		
		// 死亡
		namespace Dead
		{
			static const uint16_t kFrame = 10;

			static const size_t kDebriNum = 16;
		}
	}

	// ウマ
	namespace HorseAnimationConfig
	{
		// 立ち
		static const uint16_t kIdleFrame = 60;

		// 移動
		namespace Move
		{
			static const uint16_t kFrame = 8;

			static const size_t kDustNum = 4;
		}

		// ジャンプ
		namespace Jump
		{
			static const uint16_t kFrame = 20;

			static const size_t kDustNum = 8;
		}

		// 着地
		namespace Landing
		{
			static const uint16_t kFrame = 20;

			static const size_t kDirectionNum = 8;

			static const size_t kDustNum = 2;
		}

		// 攻撃
		static const uint16_t kAttackFrame = 10;

		// 被弾
		namespace Hit
		{
			static const uint16_t kFrame = 4;

			// ブレ
			static const float kSwing = 0.2f;
		}

		// 死亡
		namespace Dead
		{
			static const uint16_t kFrame = 10;

			static const size_t kDebriNum = 16;
		}
	}

	// スライム
	namespace SlimeAnimationConfig
	{
		// 立ち
		static const uint16_t kIdleFrame = 60;

		// 着地
		namespace Landing
		{
			static const uint16_t kFrame = 20;

			static const size_t kDirectionNum = 4;

			static const size_t kDustNum = 2;
		}

		// 被弾
		namespace Hit
		{
			static const uint16_t kFrame = 4;

			// ブレ
			static const float kSwing = 0.2f;
		}

		// 死亡
		namespace Dead
		{
			static const uint16_t kFrame = 10;

			static const size_t kDebriNum = 16;
		}
	}
}
