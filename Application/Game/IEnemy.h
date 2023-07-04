#pragma once
#include "ICharacter.h"

namespace YGame
{
    class IEnemy :
        public ICharacter
    {

	public:

		/// <summary>
		/// XV
		/// </summary>
		virtual void Update() override;

		/// <summary>
		/// •`‰æ
		/// </summary>
		virtual void Draw() override;

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
