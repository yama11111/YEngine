#pragma once
#include "Vector3.h"
#include "Vector4.h"
#include "ViewProjection.h"
#include <cstdint>

namespace YGame
{
	class WaveParticle
	{

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void StaticInitialize();

		/// <summary>
		/// 発生
		/// </summary>
		/// <param name="aliveFrame"> : 生存時間</param>
		/// <param name="pos"> : 位置</param>
		/// <param name="rota"> : 回転</param>
		/// <param name="endScale"> : 最終スケール</param>
		/// <param name="color"> : 色</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		static void Emit(
			const uint32_t aliveFrame,
			const YMath::Vector3& pos,
			const YMath::Vector3& rota,
			const float endScale,
			const YMath::Vector4& color,
			ViewProjection* pVP);

	};
}
