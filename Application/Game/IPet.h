#pragma once
#include "IGameCharacter.h"

namespace YGame
{
    class IPet :
        public IGameCharacter
    {

    public:

        IPet() = default;

        ~IPet() = default;

    };
}
