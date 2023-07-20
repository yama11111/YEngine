#pragma once
#include "ICharacter.h"

namespace YGame
{
	class IAttack :
		public ICharacter
	{

	public:

		/// <summary>
		/// �Փ˔���
		/// </summary>
		/// <param name="info"> : �Փˎ����</param>
		virtual void OnCollision(const CollisionInfo& info) override;
	
	public:

		IAttack() = default;

		virtual ~IAttack() = default;

	};
}