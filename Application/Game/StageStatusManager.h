#pragma once
#include <cstdint>
#include <array>
#include <vector>

namespace YGame
{
	class StageStatusManager
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
		void Clear();
		
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

	public:

		/// <summary>
		/// 現在のステージのステータスを保存
		/// </summary>
		/// <param name="score"> : スコア</param>
		void SetCurrentStageStatus(const uint32_t score);
		
		/// <summary>
		/// ステージ番号設定
		/// </summary>
		/// <param name="index"> : ステージ番号</param>
		void SetStageIndex(const uint32_t index);

	public:
		
		static StageStatusManager* GetInstance();
	
	private:

		StageStatusManager() = default;
		~StageStatusManager() = default;
		StageStatusManager(const StageStatusManager&) = delete;
		const StageStatusManager& operator=(const StageStatusManager&) = delete;
	
	private:

		std::vector<StageStatus> statuses_;
		
		uint32_t stageIndex = 0;	
	};
}
