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

        // スピード
        YMath::Speed speed_;

        // ジャンプカウンター
        int jumpCount_ = 0;

        // キャラクターステータス
        CharacterStatus status_;
    };
}

