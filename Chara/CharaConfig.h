#pragma once

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
		const float RisePower = 4.5f;
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
}