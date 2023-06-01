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

		// 生存フラグ
		bool isAlive_ = true;

		// 体力
		unsigned int hp_ = 0;

		// 攻撃力
		unsigned int attack = 0;

	};
}

