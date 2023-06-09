#include "CharacterStatus.h"

using YGame::CharacterStatus;

void CharacterStatus::Initialize(const uint32_t hp, const uint32_t attack)
{
	// 体力設定
	SetHP(hp);
	
	// 攻撃力設定
	SetAttack(attack);
}

void CharacterStatus::Damage(const uint32_t attack)
{
	// 死んでるなら 弾く
	if (isAlive_ == false) { return; }
	
	// 無敵なら 弾く
	if (isInvincible_) { return; }

	// 攻撃力 が HP 超えていたら
	if (hp_ <= attack)
	{
		// 死ぬ
		hp_ = 0;
		
		isAlive_ = false;
	}
	// それ以外なら
	else
	{
		hp_ -= attack;
	}
}

void CharacterStatus::SetHP(const uint32_t hp)
{
	// 0以下なら
	if (hp_ <= 0)
	{
		// 0にする
		hp_ = 0;

		// 死ぬ
		isAlive_ = false;
	}
	// それ以外なら
	else
	{
		// 代入
		hp_ = hp;
	}
}

void CharacterStatus::SetAttack(const uint32_t attack)
{
	// 0以下なら
	if (attack_ <= 0)
	{
		// 0にする
		attack_ = 0;
	}
	// それ以外なら
	else
	{
		// 代入
		attack_ = attack;
	}
}

void CharacterStatus::SetInvincible(const bool isInvincible)
{
	// 代入
	isInvincible_ = isInvincible;
}
