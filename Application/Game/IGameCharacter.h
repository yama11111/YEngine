#pragma once
#include "IGameObject.h"
#include "CharacterStatus.h"
#include "Speed.h"

namespace YGame
{
    class IGameCharacter :
        public IGameObject
    {

    public:
    
    public:

        IGameCharacter() = default;
        
        ~IGameCharacter() = default;

    protected:

        // �X�s�[�h
        YMath::Speed speed_;

        // �W�����v�J�E���^�[
        int jumpCount_ = 0;

        // �L�����N�^�[�X�e�[�^�X
        CharacterStatus status_;
    };
}

