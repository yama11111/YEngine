/**
 * @file StarParticle.h
 * @brief 星パーティクルクラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "Vector3.h"
#include "ViewProjection.h"

namespace YGame
{
	class StarParticle
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
			const YMath::Vector3& direction,
			ViewProjection* pVP);

	};
}
