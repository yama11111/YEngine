#pragma once
#include "Timer.h"

namespace YGame
{
	class CharacterStatus final
	{

	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="hp"> : �̗�</param>
		/// <param name="attack"> : �U����</param>
		/// <param name="invincibleTime"> : ���G����</param>
		void Initialize(const uint32_t hp, const uint32_t attack, const uint32_t invincibleTime);

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

		/// <summary>
		/// �_���[�W
		/// </summary>
		/// <param name="attack"> : �U����</param>
		/// <param name="isInvincible"> : ���G�ɂ��邩</param>
		void Damage(const uint32_t attack, const bool isInvincible);

	public:

		/// <summary>
		/// �����t���O�擾
		/// </summary>
		/// <returns>�����t���O</returns>
		bool IsAlive() const { return isAlive_; }

		/// <summary>
		/// HP�擾
		/// </summary>
		/// <returns>HP</returns>
		uint32_t HP() const { return hp_; }
		
		/// <summary>
		/// �U���͎擾
		/// </summary>
		/// <returns>�U����</returns>
		uint32_t Attack() const { return attack_; }
		
		/// <summary>
		/// ���G���[�h�擾
		/// </summary>
		/// <returns>���G���[�h</returns>
		bool IsInvincible() const { return isInvincible_; }

	public:

		/// <summary>
		/// HP�ݒ�
		/// </summary>
		/// <param name="hp"> : HP</param>
		void SetHP(const uint32_t hp);

		/// <summary>
		/// �U���͐ݒ�
		/// </summary>
		/// <param name="attack"> : �U����</param>
		void SetAttack(const uint32_t attack);
		
		/// <summary>
		/// ���G���[�h�ݒ�
		/// </summary>
		/// <param name="isInvincible"> : ���G���[�h</param>
		void SetInvincible(const bool isInvincible);
		
		/// <summary>
		/// ���G���Ԑݒ�
		/// </summary>
		/// <param name="invincibleTime">���G����</param>
		void SetInvincibleTime(const uint32_t invincibleTime);
	
	public:

		CharacterStatus() = default;
		
		~CharacterStatus() = default;

	private:

		// �����t���O
		bool isAlive_ = true;

		// �̗�
		uint32_t hp_ = 0;

		// �U����
		uint32_t attack_ = 0;
		
		// ���G���[�h
		bool isInvincible_ = true;

		// ���G�^�C�}�[
		YMath::Timer invincibleTimer_;

	};
}

