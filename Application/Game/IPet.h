#pragma once
#include "ICharacter.h"

namespace YGame
{
	class IPet :
		public ICharacter
	{

	public:

		/// <summary>
		/// �Փ˔���
		/// </summary>
		/// <param name="info"> : �Փˎ����</param>
		virtual void OnCollision(const CollisionInfo& info) override;

	public:

		IPet() = default;

		~IPet() = default;

	};
}
