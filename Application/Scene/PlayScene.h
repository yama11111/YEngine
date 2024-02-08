/**
 * @file PlayScene.h
 * @brief ゲームプレイシーンクラス
 * @author Yamanaka Rui
 * @date 2024/01/18
 */

#pragma once
#include "BaseScene.h"
#include "PauseManager.h"
#include "ScoreManager.h"
#include "UIDrawer.h"
#include "BeginingDrawer.h"

#include "Level.h"

namespace YGame
{
	// ゲームシーン
	class PlayScene final : 
		public BaseScene
	{

	public:

		// レベル
		Level* pLevel_ = nullptr;

		// UIマネージャー
		UIDrawer uiDra_;

		// 開始演出描画クラス
		BeginingDrawer beginingDra_;
		
		// 開始フラグ
		bool isStart_ = false;
		
		// 停止フラグ
		bool isStop_ = false;

		// ポーズ
		PauseManager pause_;

	public:

		/// <summary>
		/// 読み込み
		/// </summary>
		void Load() override;

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize() override;

		/// <summary>
		/// 終了処理
		/// </summary>
		void Finalize() override;

		/// <summary>
		/// 更新
		/// </summary>
		void Update() override;

		/// <summary>
		/// 描画
		/// </summary>
		void Draw() override;

	public:

		// コンストラクタ
		PlayScene() = default;

		// デストラクタ
		~PlayScene() = default;

	};
}
