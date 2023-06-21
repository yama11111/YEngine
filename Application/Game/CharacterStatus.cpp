#include "CharacterStatus.h"

using YGame::CharacterStatus;

void CharacterStatus::Initialize(const uint32_t hp, const uint32_t attack, const uint32_t invincibleTime)
{
	// 体力設定
	SetHP(hp);
	
	// 攻撃力設定
	SetAttack(attack);

	// 無敵時間設定
	SetInvincibleTime(invincibleTime);
}

void CharacterStatus::Update()
{
	// 無敵じゃないなら弾く
	if (isInvincible_ == false) { return; }

	// タイマー更新
	invincibleTimer_.Update();

	// タイマー終了したら
	if (invincibleTimer_.IsEnd())
	{
		// タイマーリセット
		invincibleTimer_.Reset(false);

		// 無敵時間終了
		isInvincible_ = false;
	}
}

void CharacterStatus::Damage(const uint32_t attack, const bool isInvincible)
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

	// 無敵にするなら
	if (isInvincible)
	{
		// 無敵タイマーリセット + スタート
		invincibleTimer_.Reset(true);

		// 無敵
		isInvincible_ = true;
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

void CharacterStatus::SetInvincibleTime(const uint32_t invincibleTime)
{
	// タイマー設定
	invincibleTimer_.SetEnd(invincibleTime);
}
