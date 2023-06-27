#pragma once
#include "ICharacter.h"

namespace YGame
{
	class IItem :
		public ICharacter
	{

	public:

		/// <summary>
		/// Õ“Ë”»’è
		/// </summary>
		/// <param name="info"> : Õ“Ëî•ñ</param>
		virtual void OnCollision(const CollisionInfo& info) override;

	public:

		IItem() = default;

		virtual ~IItem() = default;

	};
}
