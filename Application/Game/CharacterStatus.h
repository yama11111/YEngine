#pragma once

namespace YGame
{
	class CharacterStatus
	{
	
	public:

		bool IsAlive() { return isAlive_; }

	public:

		CharacterStatus() = default;
		
		~CharacterStatus() = default;

	private:

		// �����t���O
		bool isAlive_ = true;

		// �̗�
		unsigned int hp_ = 0;

		// �U����
		unsigned int attack = 0;

	};
}

