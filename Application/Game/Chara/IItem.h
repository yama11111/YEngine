#pragma once
#include "BaseCharacter.h"

namespace YGame
{
	class IItem :
		public BaseCharacter
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
