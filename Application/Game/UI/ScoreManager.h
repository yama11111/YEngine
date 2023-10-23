#pragma once
#include <cstdint>
#include <memory>
#include <vector>

namespace YGame
{
	class ScoreManager final
	{

	public:

		/// <summary>
		/// 読み込み
		/// </summary>
		void Load();

		/// <summary>
		/// 保存
		/// </summary>
		void Save();

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();
	
	public:

		/// <summary>
		///	スコア計測開始
		/// </summary>
		void StartScoreMeasurement();
		
		/// <summary>
		/// スコア計測終了
		/// </summary>
		void EndScoreMeasurement();
	
	public:

		/// <summary>
		/// スコア加算
		/// </summary>
		/// <param name="scoreVal"> : スコア値</param>
		void AddScore(const uint32_t scoreVal);

		/// <summary>
		/// スコア取得
		/// </summary>
		/// <param name="index"> : インデックス</param>
		/// <returns>スコア</returns>
		uint32_t Score(const size_t index);

		/// <summary>
		/// スコア取得 (現在)
		/// </summary>
		/// <returns>スコア</returns>
		uint32_t ScoreInCurrentStage();

	public:

		static ScoreManager* GetInstance();

	private:

		// スコア
		std::vector<uint32_t> scores_;

		// 現在スコア
		uint32_t currentScore_ = 0;

	private:

		ScoreManager() = default;
		~ScoreManager() = default;
		ScoreManager(const ScoreManager&) = delete;
		const ScoreManager& operator=(const ScoreManager&) = delete;

	};
}
