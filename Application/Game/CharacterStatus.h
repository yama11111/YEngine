#pragma once
#include <cstdint>

namespace YGame
{
	class CharacterStatus
	{

	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="hp"> : 体力</param>
		/// <param name="attack"> : 攻撃力</param>
		void Initialize(const uint32_t hp, const uint32_t attack);

		/// <summary>
		/// ダメージ
		/// </summary>
		/// <param name="attack"> : 攻撃力</param>
		void Damage(const uint32_t attack);

	public:

		/// <summary>
		/// 生存フラグ取得
		/// </summary>
		/// <returns>生存フラグ</returns>
		bool IsAlive() const { return isAlive_; }

		/// <summary>
		/// HP取得
		/// </summary>
		/// <returns>HP</returns>
		uint32_t HP() const { return hp_; }
		
		/// <summary>
		/// 攻撃力取得
		/// </summary>
		/// <returns>攻撃力</returns>
		uint32_t Attack() const { return attack_; }
		
		/// <summary>
		/// 無敵モード取得
		/// </summary>
		/// <returns>無敵モード</returns>
		bool IsInvincible() const { return isInvincible_; }

	public:

		/// <summary>
		/// HP設定
		/// </summary>
		/// <param name="hp"> : HP</param>
		void SetHP(const uint32_t hp);

		/// <summary>
		/// 攻撃力設定
		/// </summary>
		/// <param name="attack"> : 攻撃力</param>
		void SetAttack(const uint32_t attack);
		
		/// <summary>
		/// 無敵モード設定
		/// </summary>
		/// <param name="isInvincible"> : 無敵モード</param>
		void SetInvincible(const bool isInvincible);
	
	public:

		CharacterStatus() = default;
		
		~CharacterStatus() = default;

	private:

		// 生存フラグ
		bool isAlive_ = true;

		// 体力
		uint32_t hp_ = 0;

		// 攻撃力
		uint32_t attack_ = 0;
		
		// 無敵モード
		bool isInvincible_ = true;

	};
}

