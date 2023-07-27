#pragma once
#include "BaseCharacter.h"

namespace YGame
{
	class IItem :
		public BaseCharacter
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
