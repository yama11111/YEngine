#pragma once
#include "BaseCharacter.h"
#include "Timer.h"

namespace YGame
{
    class IEnemy :
        public BaseCharacter
    {

	public:

		/// <summary>
		/// 衝突前更新
		/// </summary>
		virtual void UpdateBeforeCollision() override;

		/// <summary>
		/// 衝突後更新
		/// </summary>
		virtual void UpdateAfterCollision() override;

    public:

        IEnemy() = default;
        
        virtual ~IEnemy() = default;

    protected:

		// ぶっ飛びタイマー
		YMath::Timer blowTim_;

    protected:

		/// <summary>
		/// 衝突時処理
		/// </summary>
		/// <param name="info"></param>
		virtual void OnCollision(const CollisionInfo& info) override;
	
		/// <summary>
		/// 被弾
		/// </summary>
		/// <param name="damage"> : ダメージ</param>
		/// <param name="isStepOn"> : 踏まれたか</param>
		virtual void Hit(const uint32_t damage, const bool isStepOn) = 0;

    };
}
