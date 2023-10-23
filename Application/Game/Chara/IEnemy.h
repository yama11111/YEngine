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
		/// 更新
		/// </summary>
		/// <param name="isUpdate"> : 更新するか</param>
		virtual void Update(const bool isUpdate);

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="info"> : 衝突時情報</param>
		virtual void OnCollision(const CollisionInfo& info) override;

    public:

        IEnemy() = default;
        
        virtual ~IEnemy() = default;

    protected:

		// ぶっ飛びタイマー
		YMath::Timer blowTim_;

    protected:
	
		/// <summary>
		/// 被弾
		/// </summary>
		/// <param name="damage"> : ダメージ</param>
		/// <param name="isStepOn"> : 踏まれたか</param>
		virtual void Hit(const uint32_t damage, const bool isStepOn) = 0;

    };
}
