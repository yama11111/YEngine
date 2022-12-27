#pragma once

namespace CharaConfig 
{
	// 重力
	const float GravityPower = 0.3f;

	// プレイヤー
	namespace Player 
	{
		// 半径 (アタリ判定)
		const float CollRad = 10.0f;
		
		// 体力
		const int HP = 2;

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
		const int CheatTime = 0;

		// スライム
		namespace Slime
		{
			// 半径 (アタリ判定)
			const float CollRad = 10.0f;

			// 体力
			const int HP = 1;
		}
	}
}