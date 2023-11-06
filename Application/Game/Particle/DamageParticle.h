#pragma once
#include "Vector3.h"
#include "ViewProjection.h"
#include <cstdint>

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
		/// <param name="damageVal"> : ダメージ量</param>
		/// <param name="pos"> : 位置</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		static void Emit(
			const uint32_t damageVal, 
			const YMath::Vector3& pos,
			ViewProjection* pVP);

	};
}
