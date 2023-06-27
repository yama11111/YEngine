#pragma once
#include "ICharacter.h"

namespace YGame
{
	class IItem :
		public ICharacter
	{

	public:

		/// <summary>
		/// �Փ˔���
		/// </summary>
		/// <param name="info"> : �Փˎ����</param>
		virtual void OnCollision(const CollisionInfo& info) override;

	public:

		IItem() = default;

		virtual ~IItem() = default;

	};
}
