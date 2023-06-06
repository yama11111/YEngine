#pragma once

namespace YGame
{
	class CharacterStatus
	{

	public:

		CharacterStatus() = default;
		
		~CharacterStatus() = default;

	protected:

		// ¶‘¶ƒtƒ‰ƒO
		bool isAlive_ = true;

		// ‘Ì—Í
		unsigned int hp_ = 0;

		// UŒ‚—Í
		unsigned int attack = 0;

	};
}

