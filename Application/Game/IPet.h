#pragma once
#include "IGameCharacter.h"

namespace YGame
{
	class IPet :
		public IGameCharacter
	{

	public:

		/// <summary>
		/// �Փ˔���
		/// </summary>
		/// <param name="pPair"> : ����̃L�����N�^�[�|�C���^</param>
		void OnCollision(IGameCharacter* pPair) override;

	public:

		IPet() = default;

		~IPet() = default;

	};
}
