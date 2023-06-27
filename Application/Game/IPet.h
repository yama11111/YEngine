#pragma once
#include "ICharacter.h"

namespace YGame
{
	class IPet :
		public ICharacter
	{

	public:

		/// <summary>
		/// Õ“Ë”»’è
		/// </summary>
		/// <param name="info"> : Õ“Ëî•ñ</param>
		virtual void OnCollision(const CollisionInfo& info) override;

	public:

		IPet() = default;

		~IPet() = default;

	};
}
