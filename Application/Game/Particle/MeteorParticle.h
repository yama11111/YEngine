/**
 * @file MeteorParticle.h
 * @brief 流星パーティクルクラス
 * @author Yamanaka Rui
 * @date 2024/03/09
 */

#pragma once
#include "Vector3.h"
#include "Vector4.h"
#include "ViewProjection.h"
#include "WorldKey.h"

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
		/// <param name="worldKey"> : 世界キー</param>
		/// <param name="pos"> : 位置</param>
		/// <param name="speed"> : 速さ</param>
		/// <param name="color"> : 色</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		static void Emit(
			const WorldKey worldKey,
			const YMath::Vector3& pos,
			const YMath::Vector3& speed,
			const YMath::Vector4& color,
			ViewProjection* pVP);

	};
}
