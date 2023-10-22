#pragma once
#include "UIButton.h"
#include "UILetterBox.h"
#include "ScoreDrawer.h"

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

	};
}

