#pragma once
#include "BaseCharacter.h"

namespace YGame
{
	class IAttack :
		public BaseCharacter
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
