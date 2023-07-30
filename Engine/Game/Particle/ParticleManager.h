#pragma once
#include "BaseParticle.h"
#include <array>

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
		/// パーティクルを挿入する
		/// </summary>
		/// <param name="tag"> : パーティクルタグ</param>
		/// <param name="particles"> : パーティクルポインタ配列</param>
		void InsertParticles(const std::string& tag, const std::list<BaseParticle*>& particles);

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

	private:

		// パーティクルポインタマップ
		std::unordered_map<
			std::string, 
			std::list<BaseParticle*>> particles_;

	private:

		ParticleManager() = default;

		~ParticleManager() = default;

		ParticleManager(const ParticleManager&) = delete;

		const ParticleManager& operator=(const ParticleManager&) = delete;
	};
}

