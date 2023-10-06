#pragma once
#include "EarthDrawer.h"
#include "StageDrawer.h"
#include "CardDrawer.h"
#include "SkydomeDrawer.h"

#include "UILetterBox.h"
#include "UIButton.h"

#include "Power.h"

namespace YGame
{
	class SelectDrawer
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

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

		void SetStageIndex(const int32_t index) { stageIndex_ = index; }

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

	private:

		// 核
		Transform core_;


		// 地球
		Transform earthTra_;
		std::unique_ptr<EarthDrawer> earthDra_;

		// ステージトランスフォーム (使う用)
		std::array<Transform, 24> aliveStages_;

		// ステージトランスフォーム (使わない用)
		Transform deadStage_;

		// ステージ描画クラス
		std::vector<std::unique_ptr<StageDrawer>> stageDras_;


		// ステージカード用トランスフォーム (親)
		std::vector<Transform> cards_;

		// ステージカード描画クラス
		std::vector<std::unique_ptr<CardDrawer>> cardDras_;


		// 黒帯
		std::unique_ptr<UILetterBox> letterBox_;

		std::unique_ptr<DrawObjectForSprite2D> logoObj_;
		std::unique_ptr<DrawObjectForSprite2D> stickObj_;
		
		std::unique_ptr<UIButton> startButton_;

		// 天球
		Transform skydomeTra_;
		std::unique_ptr<SkydomeDrawer> skydome_;


		// ----- アニメーション ----- //

		int32_t stageIndex_ = 0;

		// 動作中か
		bool isAct_ = false;


		// 開始時回転用イージング
		YMath::Ease<float> startRotaEas_;

		// 開始時回転用タイマー
		YMath::Timer startRotaTim_;


		// ステージ回転用イージング
		YMath::Ease<float> stageRotaEas_;

		// ステージ回転用パワー
		std::vector<YMath::Power> stageRotaPows_;
	
	private:

		static Sprite2D* spLogoSpr_;

		static Sprite2D* spStickSpr_;

		static Sprite2D* spButtonSpr_;

	private:

		// アニメーションの回転更新
		void UpdateRotaAnimation();

	};
}
