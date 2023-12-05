#pragma once
#include "UIButton.h"
#include "UILetterBox.h"
#include "ScoreDrawer.h"
#include "SpeedLevelDrawer.h"
#include "CoinCountDrawer.h"

namespace YGame
{
	class UIDrawer final
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
		/// 開始アニメーション
		/// </summary>
		void PlayStartAnimation();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();
	
	public:

		/// <summary>
		/// 読み込み
		/// </summary>
		static void LoadResource();

	private:
		
		// レターボックス
		std::unique_ptr<UILetterBox> letterBox_;


		// ジャンプボタン
		std::unique_ptr<UIButton> buttonJump_;
		
		// ジャンプUI
		std::unique_ptr<BaseDrawObject> uiJump_;
		

		// 攻撃ボタン
		std::unique_ptr<UIButton> buttonAttack_;

		// 攻撃UI
		std::unique_ptr<BaseDrawObject> uiAttack_;
		

		// スコア
		Transform scoreTrfm_;
		std::unique_ptr<ScoreDrawer> scoreDra_;

		// コイン
		Transform coinTrfm_;
		std::unique_ptr<CoinCountDrawer> coinDra_;

		// スピードレベル
		Transform speedTrfm_;
		std::unique_ptr<SpeedLevelDrawer> speedDra_;

	};
}

