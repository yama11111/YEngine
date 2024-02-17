/**
 * @file BaseStageDrawer.h
 * @brief ステージ描画基底クラス
 * @author Yamanaka Rui
 * @date 2024/02/17
 */

#pragma once
#include "BaseDrawer.h"
#include "CBOutline.h"
#include "WorldKey.h"

namespace YGame
{
    class BaseStageDrawer :
        public BaseDrawer
    {

    public:

        BaseStageDrawer() = default;

        ~BaseStageDrawer() = default;

    protected:

        // アウトライン定数バッファ
        std::unique_ptr<ConstBufferObject<CBOutline>> cbOutline_;

        // 世界キー
        WorldKey worldKey_;
    };
}
