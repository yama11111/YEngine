#pragma once
#include <cstdint>
#include <array>
#include <vector>

namespace YGame
{
	class StageManager
	{
	
	public:

		// ステージステータス
		struct StageStatus
		{
			bool isTutorial = false;
			std::array<uint32_t, 3> mission;
			std::array<bool, 3> isMissionClear;
		};
	
	public:
		
		/// <summary>
		/// 読み込み
		/// </summary>
		void Load();
		
		/// <summary>
		/// 書き込み
		/// </summary>
		void Save();

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// リセット
		/// </summary>
		void Reset();

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

	public:

		/// <summary>
		/// ゲームオーバー
		/// </summary>
		void GameOver();

		/// <summary>
		/// ステージクリア
		/// </summary>
		void ClearStage();
		
	public:

		/// <summary>
		/// 現在のステージ番号
		/// </summary>
		/// <returns>ステージ番号</returns>
		uint32_t CurrentStageIndex() const;

		/// <summary>
		/// ステージ最大数
		/// </summary>
		/// <returns>ステージ最大数</returns>
		uint32_t MaxStageNum() const;

		/// <summary>
		/// ステージステータス
		/// </summary>
		/// <param name="index"> : ステージ番号</param>
		/// <returns>ステージステータス</returns>
		StageStatus Status(const size_t index) const;

		/// <summary>
		/// ステージ番号設定
		/// </summary>
		/// <param name="index"> : ステージ番号</param>
		void SetStageIndex(const uint32_t index);

	public:
		
		static StageManager* GetInstance();
	
	private:

		StageManager() = default;
		~StageManager() = default;
		StageManager(const StageManager&) = delete;
		const StageManager& operator=(const StageManager&) = delete;
	
	private:

		std::vector<StageStatus> statuses_;
		
		uint32_t stageIndex = 0;

		bool isGameOver_ = false;

		bool isStageClear_ = false;
	
	};
}
