#pragma once
#include "IGameCharacter.h"

namespace YGame
{
    class IEnemy :
        public IGameCharacter
    {

	public:

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw() override;

		/// <summary>
		/// 衝突判定
		/// </summary>
		/// <param name="pPair"> : 相手のキャラクターポインタ</param>
		virtual void OnCollision(IGameCharacter* pPair) override;

    public:

        IEnemy() = default;
        
        virtual ~IEnemy() = default;

    protected:

    };
}
