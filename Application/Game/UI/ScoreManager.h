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
		const uint32_t Score(const size_t index) const;

		/// <summary>
		/// スコア取得 (現在)
		/// </summary>
		/// <returns>スコア</returns>
		const uint32_t ScoreInCurrentStage() const;
	
	public:

		/// <summary>
		/// コイン数加算
		/// </summary>
		/// <param name="coinVal"> : コイン数</param>
		void AddCoin(const uint32_t coinVal);

		/// <summary>
		/// コイン取得
		/// </summary>
		/// <returns>コイン</returns>
		const uint32_t Coin() const;

	public:
		
		/// <summary>
		/// HP設定
		/// </summary>
		/// <param name="hp"> : HP</param>
		void SetHP(const uint32_t hp);

		/// <summary>
		/// 最大HP設定
		/// </summary>
		/// <param name="maxHP"> : 最大HP</param>
		void SetMaxHP(const uint32_t maxHP);

		/// <summary>
		/// HP取得
		/// </summary>
		/// <returns>HP</returns>
		const uint32_t HP() const;

		/// <summary>
		/// 最大HP取得
		/// </summary>
		/// <returns>最大HP</returns>
		const uint32_t MaxHP() const;

	public:

		/// <summary>
		/// 速度レベル加算
		/// </summary>
		void AddSpeedLevel();

		/// <summary>
		/// 速度レベル取得
		/// </summary>
		/// <returns>速度レベル</returns>
		const uint32_t SpeedLevel() const;
	
	public:

		static ScoreManager* GetInstance();

	private:

		// スコア
		std::vector<uint32_t> scores_;

		// 現在スコア
		uint32_t currentScore_ = 0;

		// コインカウンター
		uint32_t coinCounter_ = 0;

		// HP
		uint32_t hp_ = 0;
		
		// 最大HP
		uint32_t maxHP_ = 0;
		
		// 速度レベル
		uint32_t speedLevel_ = 0;

	private:

		ScoreManager() = default;
		~ScoreManager() = default;
		ScoreManager(const ScoreManager&) = delete;
		const ScoreManager& operator=(const ScoreManager&) = delete;

	};
}
