#pragma once
#include "UINumber.h"
#include "CBColor.h"
#include "Ease.h"
#include "Power.h"
#include <memory>

namespace YGame
{
	class ScoreManager final
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();
	
	public:

		/// <summary>
		/// リソース読み込み
		/// </summary>
		static void LoadResource();


		static ScoreManager* GetInstance();

	private:

		ScoreManager() = default;
		~ScoreManager() = default;
		ScoreManager(const ScoreManager&) = delete;
		const ScoreManager& operator=(const ScoreManager&) = delete;

	private:

		// UI
		std::unique_ptr<UINumber> uiNum_;

		// スコア
		uint32_t score_;

	};
}
