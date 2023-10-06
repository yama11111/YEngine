#pragma once
#include "BaseCharacter.h"

namespace YGame
{
    class IEnemy :
        public BaseCharacter
    {

	public:

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="info"> : 衝突時情報</param>
		virtual void OnCollision(const CollisionInfo& info) override;

    public:

        IEnemy() = default;
        
        virtual ~IEnemy() = default;

    protected:

		/// <summary>
		/// 被弾
		/// </summary>
		virtual void Hit();

    };
}
