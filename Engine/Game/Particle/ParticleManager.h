#pragma once
#include "BaseParticle.h"
#include <list>

namespace YGame
{
	// パーティクルマネージャー
	class ParticleManager
	{
	
	public:
		
		/// <summary>
		/// シングルトンインスタンスポインタ取得
		/// </summary>
		/// <returns>インスタンスポインタ</returns>
		static ParticleManager* GetInstance();

	public:

		/// <summary>
		/// クリア
		/// </summary>
		void Clear();

		/// <summary>
		/// 挿入
		/// </summary>
		/// <param name="newParticle"> : パーティクル (動的インスタンス)</param>
		void PushBack(BaseParticle* newParticle);

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

	private:

		// パーティクルリスト
		std::list<std::unique_ptr<BaseParticle>> particles_;

	private:

		ParticleManager() = default;

		~ParticleManager() = default;

		ParticleManager(const ParticleManager&) = delete;

		const ParticleManager& operator=(const ParticleManager&) = delete;
	};
}

