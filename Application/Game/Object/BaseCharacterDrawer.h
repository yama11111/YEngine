/**
 * @file BaseCharacterDrawer.h
 * @brief キャラクター描画基底クラス
 * @author Yamanaka Rui
 * @date 2024/02/17
 */

#pragma once
#include "BaseDrawer.h"
#include "CBOutline.h"
#include "HitActor.h"
#include "SlimeActor.h"

namespace YGame
{
    class BaseCharacterDrawer :
        public BaseDrawer
    {

    public:

        BaseCharacterDrawer() = default;

        ~BaseCharacterDrawer() = default;

    protected:

        // アウトライン定数バッファ
        std::unique_ptr<ConstBufferObject<CBOutline>> cbOutline_;

        // スライム
        SlimeActor slimeActor_;

        // 被弾
        HitActor hitActor_;
    };
}
