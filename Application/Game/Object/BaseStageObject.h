#pragma once
#include "GameObject.h"

namespace YGame
{
	class BaseStageObject :
		public GameObject
	{

	public:

		/// <summary>
		/// 位置更新
		/// </summary>
		void UpdatePos();
		
		/// <summary>
		/// ワールド座標取得
		/// </summary>
		/// <returns>ワールド座標</returns>
		YMath::Vector3 WorldPos() const override;

	};
}
