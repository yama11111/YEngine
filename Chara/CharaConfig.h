#pragma once
#include "Vector4.h"

namespace CharaConfig 
{
	// プレイヤー
	namespace Player 
	{
		// 半径 (アタリ判定)
		const float CollRad = 4.5f;
		// 体力
		const int HP = 1;
		// 無敵時間
		const int CheatTime = 20;

		// 最大ジャンプ回数
		const int MaxJumpCount = 1;
		// ジャンプ力
		const float RisePower = 6.0f;
	}

	// エネミー
	namespace Enemy
	{
		// 無敵時間
		const int CheatTime = 5;

		// スライム
		namespace Slime
		{
			// 半径 (アタリ判定)
			const float CollRad = 8.0f;

			// 体力
			const int HP = 1;
		}
	}

	// スライムアニメーション
	namespace SlimeAct
	{
		// ブヨブヨ時間
		const unsigned int Frame = 4;
		// パワー
		const float Power = 2.0f;
		// 伸縮量
		const float ElasticityValue = 0.1f;
		// つぶれる量 (着地時)
		const float SquashValue = 0.25f;
	}

	// ヒットアニメーション
	namespace HitAct
	{
		// 振動量
		const float ShakeValue = 3.0f;

		// 色
		const YMath::Vector4 Color = { 1.0f, 0.0f, 0.0f, 1.0f };

		// 透過量
		const float AlphaValue = 0.5f;
	}
}