/**
 * @file DamageParticle.h
 * @brief ダメージパーティクルクラス
 * @author Yamanaka Rui
 * @date 2024/03/09
 */

#pragma once
#include "Vector3.h"
#include "ViewProjection.h"
#include <cstdint>
#include "WorldKey.h"

namespace YGame
{
	class DamageParticle
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
		/// <param name="damageVal"> : ダメージ量</param>
		/// <param name="pos"> : 位置</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		static void Emit(
			const WorldKey worldKey,
			const uint32_t damageVal, 
			const YMath::Vector3& pos,
			ViewProjection* pVP);

	};
}
