#include "CharacterStatus.h"

using YGame::CharacterStatus;

void CharacterStatus::Initialize(const uint32_t hp, const uint32_t attack)
{
	// ‘Ì—Íİ’è
	SetHP(hp);
	
	// UŒ‚—Íİ’è
	SetAttack(attack);
}

void CharacterStatus::Damage(const uint32_t attack)
{
	// €‚ñ‚Å‚é‚È‚ç ’e‚­
	if (isAlive_ == false) { return; }
	
	// –³“G‚È‚ç ’e‚­
	if (isInvincible_) { return; }

	// UŒ‚—Í ‚ª HP ’´‚¦‚Ä‚¢‚½‚ç
	if (hp_ <= attack)
	{
		// €‚Ê
		hp_ = 0;
		
		isAlive_ = false;
	}
	// ‚»‚êˆÈŠO‚È‚ç
	else
	{
		hp_ -= attack;
	}
}

void CharacterStatus::SetHP(const uint32_t hp)
{
	// 0ˆÈ‰º‚È‚ç
	if (hp_ <= 0)
	{
		// 0‚É‚·‚é
		hp_ = 0;

		// €‚Ê
		isAlive_ = false;
	}
	// ‚»‚êˆÈŠO‚È‚ç
	else
	{
		// ‘ã“ü
		hp_ = hp;
	}
}

void CharacterStatus::SetAttack(const uint32_t attack)
{
	// 0ˆÈ‰º‚È‚ç
	if (attack_ <= 0)
	{
		// 0‚É‚·‚é
		attack_ = 0;
	}
	// ‚»‚êˆÈŠO‚È‚ç
	else
	{
		// ‘ã“ü
		attack_ = attack;
	}
}

void CharacterStatus::SetInvincible(const bool isInvincible)
{
	// ‘ã“ü
	isInvincible_ = isInvincible;
}
