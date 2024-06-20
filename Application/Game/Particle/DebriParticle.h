/**
 * @file DebriParticle.h
 * @brief 破片パーティクルクラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "Vector3.h"
#include "ViewProjection.h"
#include "WorldKey.h"

namespace YGame
{
	class DebriParticle
	{

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void StaticInitialize();

		/// <summary>
		/// 発生
		/// </summary>
		/// <param name="worldKey"> : 世界キー</param>
		/// <param name="num"> : 数</param>
		/// <param name="pos"> : 位置</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		static void Emit(
			const WorldKey worldKey,
			const size_t num,
			const YMath::Vector3& pos,
			ViewProjection* pVP);

	};
}
