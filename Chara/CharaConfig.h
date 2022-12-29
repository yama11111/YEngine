#pragma once
#include "Vec4.h"

namespace CharaConfig 
{
	// 重力
	const float GravityPower = 0.3f;

	// 攻撃範囲
	const float AttackRange = 2.0f;

	// プレイヤー
	namespace Player 
	{
		// 半径 (アタリ判定)
		const float CollRad = 4.5f;
		
		// 体力
		const int HP = 100;

		// 無敵時間
		const int CheatTime = 20;

		// 最大ジャンプ回数
		const int MaxJumpCount = 2;

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
			const float CollRad = 4.5f;

			// 体力
			const int HP = 100;
		}
	}

	// スライムアニメーション
	namespace SlimeAct
	{
		// ブヨブヨ時間
		const int Frame = 4;

		// 伸縮量
		const float ElasticityValue = 0.5f;

		// つぶれる量 (着地時)
		const float SquashValue = 0.75f;
	}

	// ヒットアニメーション
	namespace HitAct
	{
		// 振動量
		const float ShakeValue = 3.0f;

		// 色
		const YMath::Vec4 Color = { 1.0f, 0.25f, 0.25f, 1.0f };

		// 透過量
		const float AlphaValue = 0.5f;
	}
}