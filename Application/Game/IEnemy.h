#pragma once
#include "BaseCharacter.h"

namespace YGame
{
    class IEnemy :
        public BaseCharacter
    {

	public:

		/// <summary>
		/// Õ“Ë”»’è
		/// </summary>
		/// <param name="info"> : Õ“Ëî•ñ</param>
		virtual void OnCollision(const CollisionInfo& info) override;

    public:

        IEnemy() = default;
        
        virtual ~IEnemy() = default;

    protected:

		/// <summary>
		/// ”í’e
		/// </summary>
		virtual void Hit();

    };
}
