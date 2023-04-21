#pragma once
#include "Particle.h"
#include <list>

namespace YGame
{
	// パーティクルマネージャー
	class ParticleManager
	{
	private:
		// パーティクルリスト
		std::list<std::unique_ptr<IParticle>> particles_;
	public:
		// 初期化
		void Initialize();
		// 更新
		void Update();
		// 描画
		void Draw();
	public:
		// 静的初期化
		static void StaticInitialize(YGame::ViewProjection* pVP);
	public:
		~ParticleManager() = default;
	};
}

