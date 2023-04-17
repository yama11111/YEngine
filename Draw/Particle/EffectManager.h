#pragma once
#include "Effect.h"

namespace YGame
{
	// エフェクトマネージャー
	class EffectManager
	{
	private:
		// エフェクトリスト
		std::list<std::unique_ptr<IEffect>> effects_;
	public:
		// 初期化
		void Initialize();
		// 更新
		void Update();
		// 描画
		void Draw();
	public:
		// 静的初期化
		static void StaticInitialize(ParticleManager* pParticleMan);
	};
}

