#pragma once
#include "IGameCharacter.h"

namespace YGame
{
	class IPet :
		public IGameCharacter
	{

	public:

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="pPair"> : 相手のキャラクターポインタ</param>
		void OnCollision(IGameCharacter* pPair) override;

	public:

		IPet() = default;

		~IPet() = default;

	};
}
