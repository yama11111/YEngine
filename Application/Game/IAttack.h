#pragma once
#include "IGameCharacter.h"
#include "BaseCollider.h"

namespace YGame
{
	class IAttack :
		public IGameObject,
		public BaseCollider
	{

	public:

		/// <summary>
		/// XV
		/// </summary>
		virtual void Update() override;

	public:

		IAttack() = default;

		virtual ~IAttack() = default;

	};
}
