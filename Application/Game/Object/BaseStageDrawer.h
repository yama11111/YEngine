/**
 * @file BaseStageDrawer.h
 * @brief ステージ描画基底クラス
 * @author Yamanaka Rui
 * @date 2024/02/17
 */

#pragma once
#include "BaseDrawer.h"
#include "CBOutline.h"

namespace YGame
{
    class BaseStageDrawer :
        public BaseDrawer
    {

    public:

        /// <summary>
        /// 更新
        /// </summary>
        virtual void Update() override;

        /// <summary>
        /// 透ける
        /// </summary>
        void UpdateSeeThrough();

        /// <summary>
        /// 親位置行列ポインタ設定
        /// </summary>
        /// <param name="pParentPosMat"> : 親位置行列ポインタ</param>
        void SetParentPosMatPointer(YMath::Matrix4* pParentPosMat);

    public:

        BaseStageDrawer() = default;

        ~BaseStageDrawer() = default;

    protected:

        // アウトライン定数バッファ
        std::unique_ptr<ConstBufferObject<CBOutline>> cbOutline_;

        // 親位置行列ポインタ
        YMath::Matrix4* pParentPosMat_ = nullptr;
        
        // 透ける
        bool isSeeThrough_ = true;

    };
}
