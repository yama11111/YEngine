#pragma once
#include "IGameCharacter.h"
#include "IPet.h"

namespace YGame
{
    class Player final :
        public IGameCharacter 
    {

    public:

        Player() = default;
        
        ~Player() = default;
    
    public:

    
    private:

        // �y�b�g�|�C���^
        IPet* pPet_ = nullptr;

    };
}
