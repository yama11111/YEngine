#include "CharacterStatus.h"

using YGame::CharacterStatus;

void CharacterStatus::Initialize(const uint32_t hp, const uint32_t attack)
{
	// �̗͐ݒ�
	SetHP(hp);
	
	// �U���͐ݒ�
	SetAttack(attack);
}

void CharacterStatus::Damage(const uint32_t attack)
{
	// ����ł�Ȃ� �e��
	if (isAlive_ == false) { return; }
	
	// ���G�Ȃ� �e��
	if (isInvincible_) { return; }

	// �U���� �� HP �����Ă�����
	if (hp_ <= attack)
	{
		// ����
		hp_ = 0;
		
		isAlive_ = false;
	}
	// ����ȊO�Ȃ�
	else
	{
		hp_ -= attack;
	}
}

void CharacterStatus::SetHP(const uint32_t hp)
{
	// 0�ȉ��Ȃ�
	if (hp_ <= 0)
	{
		// 0�ɂ���
		hp_ = 0;

		// ����
		isAlive_ = false;
	}
	// ����ȊO�Ȃ�
	else
	{
		// ���
		hp_ = hp;
	}
}

void CharacterStatus::SetAttack(const uint32_t attack)
{
	// 0�ȉ��Ȃ�
	if (attack_ <= 0)
	{
		// 0�ɂ���
		attack_ = 0;
	}
	// ����ȊO�Ȃ�
	else
	{
		// ���
		attack_ = attack;
	}
}

void CharacterStatus::SetInvincible(const bool isInvincible)
{
	// ���
	isInvincible_ = isInvincible;
}
