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
#include "WorldKey.h"

namespace YGame
{
    class BaseCharacterDrawer :
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
    
        /// <summary>
        /// 世界キー設定
        /// </summary>
        /// <param name="worldKey"> : 世界キー</param>
        virtual void SetWorldKey(const WorldKey worldKey);

    public:

        BaseCharacterDrawer() = default;

        ~BaseCharacterDrawer() = default;

    protected:

        // 今どの世界にいるか
        WorldKey worldKey_{};

        // アウトライン定数バッファ
        std::unique_ptr<ConstBufferObject<CBOutline>> cbOutline_;

        // スライム
        SlimeActor slimeActor_;

        // 被弾
        HitActor hitActor_;

        // 親位置行列ポインタ
        YMath::Matrix4* pParentPosMat_ = nullptr;

        // 透ける
        bool isSeeThrough_ = true;
    };
}
