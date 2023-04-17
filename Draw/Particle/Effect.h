#pragma once
#include "ParticleManager.h"

namespace YGame
{
	// エフェクト基底クラス
	class IEffect
	{
	public:
		// 生存フラグ
		bool isAlive_ = false;
	public:
		// 更新
		virtual void Update() = 0;
		// 描画
		virtual void Draw() = 0;
	protected:
		// 静的パーティクルマネージャーポインタ
		static ParticleManager* spParticleMan_;
	public:
		// 静的初期化
		static void StaticInitialize(ParticleManager* pParticleMan);
	public:
		// デストラクタ
		virtual ~IEffect() = default;
	};
}

