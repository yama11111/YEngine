#pragma once

// 描画用クラス
namespace DrawerConfig
{
	// プレイヤー
	namespace Player 
	{
		// 立ちモーション
		namespace Idle
		{
			// 間隔
			const unsigned int IntervalTime = 10;

			// ぷよぷよアニメーション
			namespace SlimeAction
			{
				// 伸縮量
				const float Value = 0.5f;

				// 時間 (F)
				const unsigned int Frame = 20;

				// 指数
				const float Power = 3.0f;
			}
		}

		// ジャンプモーション
		namespace Jump
		{
			// ぷよぷよアニメーション
			namespace SlimeAction
			{
				// 伸縮量
				const float Value = 0.5f;

				// 時間 (F)
				const unsigned int Frame = 20;

				// 指数
				const float Power = 3.0f;
			}
		}

		// 着地モーション
		namespace Landing
		{
			// ぷよぷよアニメーション
			namespace SlimeAction
			{
				// 伸縮量
				const float Value = 0.5f;
				
				// 時間 (F)
				const unsigned int Frame = 20;

				// 指数
				const float Power = 3.0f;
			}
		}
	}

	// フィルター
	namespace Filter 
	{
		// 立ちモーション
		namespace Idle
		{
			// 間隔
			const unsigned int IntervalTime = 10;
		}
	}

	// ブロック
	namespace Block
	{
		// 立ちモーション
		namespace Idle
		{
			// 間隔
			const unsigned int IntervalTime = 10;
		}
	}

	// ゲート
	namespace Gate
	{
		// 立ちモーション
		namespace Idle
		{
			// 間隔
			const unsigned int IntervalTime = 10;
		}
	}

	// ゴール
	namespace Goal
	{
		// 立ちモーション
		namespace Idle
		{
			// 間隔
			const unsigned int IntervalTime = 10;
		}
	}
}