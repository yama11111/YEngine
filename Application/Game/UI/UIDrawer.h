/**
 * @file UIDrawer.h
 * @brief インゲームのUIを表示するクラス
 * @author Yamanaka Rui
 * @date 2024/01/05
 */

#pragma once
#include "UILetterBox.h"
#include "ScoreDrawer.h"
#include "InstructionsDrawer.h"
#include "StatusDrawer.h"

namespace YGame
{
	class UIDrawer final
	{
	
	public:

		/// <summary>
		/// 読み込み
		/// </summary>
		static void LoadResource();

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
		/// 開始アニメーション
		/// </summary>
		void PlayStartAnimation();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

	private:
		
		// レターボックス
		std::unique_ptr<UILetterBox> letterBox_;

		// 操作説明
		Transform instTrfm_;
		std::unique_ptr<InstructionsDrawer> instDra_;

		// ステータス
		Transform statusTrfm_;
		std::unique_ptr<StatusDrawer> statusDra_;

		// スコア
		Transform scoreTrfm_;
		std::unique_ptr<ScoreDrawer> scoreDra_;

		// ポーズ
		std::unique_ptr<UIButton> pauseButton_;
	};
}

