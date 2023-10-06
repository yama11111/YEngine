#pragma once
#include "Vector3.h"
#include "ViewProjection.h"

namespace YGame
{
	class ExplosionParticle
	{

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void StaticInitialize();

		/// <summary>
		/// 発生
		/// </summary>
		/// <param name="num"> : 数</param>
		/// <param name="pos"> : 位置</param>
		/// <param name="powerDirection"> : 力のかかる向き</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		static void Emit(
			const size_t num,
			const YMath::Vector3& pos,
			const YMath::Vector3& powerDirection,
			ViewProjection* pVP);

	};
}
