#pragma once
#include <cstdint>

namespace YGame
{
	class CharacterStatus
	{

	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="hp"> : �̗�</param>
		/// <param name="attack"> : �U����</param>
		void Initialize(const uint32_t hp, const uint32_t attack);

		/// <summary>
		/// �_���[�W
		/// </summary>
		/// <param name="attack"> : �U����</param>
		void Damage(const uint32_t attack);

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

	};
}

