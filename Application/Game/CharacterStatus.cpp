#include "CharacterStatus.h"
#include <imgui.h>

using YGame::CharacterStatus;

void CharacterStatus::Initialize(const uint32_t hp, const uint32_t attack, const uint32_t invincibleTime)
{
	isAlive_ = true;

	// �̗͐ݒ�
	SetHP(hp);
	
	// �U���͐ݒ�
	SetAttack(attack);

	// ���G���Ԑݒ�
	SetInvincibleTime(invincibleTime);

	isInvincible_ = false;
}

void CharacterStatus::Update()
{
	// ���G����Ȃ��Ȃ�e��
	if (isInvincible_ == false) { return; }

	// �^�C�}�[�X�V
	invincibleTimer_.Update();

	// �^�C�}�[�I��������
	if (invincibleTimer_.IsEnd())
	{
		// �^�C�}�[���Z�b�g
		invincibleTimer_.Reset(false);

		// ���G���ԏI��
		isInvincible_ = false;
	}
}

void CharacterStatus::Damage(const uint32_t attack, const bool isInvincible)
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

	// ���G�ɂ���Ȃ�
	if (isInvincible)
	{
		// ���G�^�C�}�[���Z�b�g + �X�^�[�g
		invincibleTimer_.Reset(true);

		// ���G
		isInvincible_ = true;
	}
}

void CharacterStatus::DrawDebugTextContent()
{
	ImGui::SetNextItemOpen(true, ImGuiCond_Once);
	if (ImGui::TreeNode("status"))
	{
		if (isAlive_)
		{
			ImGui::Text("isAlive : true");
		}
		else
		{
			ImGui::Text("isAlive : false");
		}

		ImGui::Text("HP : %5d", hp_);

		ImGui::Text("Attack : %5d", attack_);
		
		if (isInvincible_)
		{
			ImGui::Text("isInvincible : true");
			
			ImGui::Text("invincibleTimer : %5f", invincibleTimer_.End() - invincibleTimer_.Current());
		}
		else
		{
			ImGui::Text("isInvincible : false");
		}

		ImGui::TreePop();
	}
}

void CharacterStatus::SetHP(const uint32_t hp)
{
	// 0�ȉ��Ȃ�
	if (hp <= 0)
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
	if (attack <= 0)
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

void CharacterStatus::SetInvincibleTime(const uint32_t invincibleTime)
{
	// �^�C�}�[�ݒ�
	invincibleTimer_.SetEnd(invincibleTime);
}
