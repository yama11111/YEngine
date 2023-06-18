#pragma once
#include "IGameCharacter.h"

namespace YGame
{
    class IEnemy :
        public IGameCharacter
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

    public:

        IEnemy() = default;
        
        virtual ~IEnemy() = default;

    protected:

    };
}
