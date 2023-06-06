#pragma once
#include "IGameCharacter.h"

namespace YGame
{
    class IEnemy :
        public IGameCharacter
    {
    
    public:

        IEnemy() = default;
        
        virtual ~IEnemy() = default;

    protected:

    };
}
