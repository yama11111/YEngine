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

		// ¶‘¶ƒtƒ‰ƒO
		bool isAlive_ = true;

		// ‘Ì—Í
		unsigned int hp_ = 0;

		// UŒ‚—Í
		unsigned int attack = 0;

	};
}

