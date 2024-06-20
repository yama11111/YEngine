/**
 * @file AfterimageParticle.h
 * @brief 残像パーティクルクラス
 * @author Yamanaka Rui
 * @date 2024/03/12
 */

#pragma once
#include "Transform.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldKey.h"

namespace YGame
{
	class AfterimageParticle
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
		/// <param name="trfm"> : トランスフォーム</param>
		/// <param name="color"> : 色</param>
		/// <param name="pModel"> : モデルポインタ</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		static void Emit(
			const WorldKey worldKey,
			const Transform& trfm,
			const YMath::Vector4& color,
			Model* pModel,
			ViewProjection* pVP);

	};
}
