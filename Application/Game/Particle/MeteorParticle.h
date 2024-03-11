/**
 * @file MeteorParticle.h
 * @brief 流星パーティクルクラス
 * @author Yamanaka Rui
 * @date 2024/03/09
 */

#pragma once
#include "Vector3.h"
#include "ViewProjection.h"

namespace YGame
{
	class MeteorParticle
	{

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void StaticInitialize();

		/// <summary>
		/// 発生
		/// </summary>
		/// <param name="pos"> : 位置</param>
		/// <param name="direction"> : 向き</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		static void Emit(
			const YMath::Vector3& pos,
			ViewProjection* pVP);

	};
}
