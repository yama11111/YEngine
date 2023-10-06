#pragma once
#include <cstdint>

namespace YGame
{
	class StageManager
	{
	
	public:
		
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

		uint32_t stageIndex = 0;

		bool isGameOver_ = false;

		bool isStageClear_ = false;
	
	};
}
