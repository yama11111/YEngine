#pragma once

namespace YGame
{
	class CharacterStatus
	{

	public:

		CharacterStatus() = default;
		
		~CharacterStatus() = default;

	protected:

		// �����t���O
		bool isAlive_ = true;

		// �̗�
		unsigned int hp_ = 0;

		// �U����
		unsigned int attack = 0;

	};
}

