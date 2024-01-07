/**
 * @file InstructionsDrawer.h
 * @brief スコアのUIを表示するクラス
 * @author Yamanaka Rui
 * @date 2024/01/06
 */

#pragma once
#include "UINumber.h"
#include "UIGauge.h"
#include "BaseDrawObject.h"
#include "ConstBufferObject.h"
#include "CBColor.h"
#include "Ease.h"
#include "Timer.h"
#include "Power.h"
#include <array>
#include <memory>

namespace YGame
{
	class ScoreDrawer
	{
	
	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		/// <returns>スコア描画クラスポインタ (動的インスタンス)</returns>
		static ScoreDrawer* Create(YMath::Matrix4* pParent, ViewProjection* pVP);

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		void Initialize(YMath::Matrix4* pParent, ViewProjection* pVP);

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();
	
	public:

		/// <summary>
		/// スコア変更アニメーション
		/// </summary>
		/// <param name="score"> : スコア</param>
		void ChangeScoreAnimation(const uint32_t score);
	
	private:

		static const size_t kMaxDigit = 6;
	
	private:

		// 現在スコア
		uint32_t currentScore_ = 0;
		// 過去スコア
		uint32_t elderScore_ = 0;
		// アニメーション用スコア
		uint32_t scoreForAnimation_ = 0;

		// トランスフォーム
		Transform transform_;

		// 数値
		std::unique_ptr<UINumber> uiNum_;
		std::array<std::unique_ptr<ConstBufferObject<CBColor>>, kMaxDigit> uiColors_;

		// アニメーション用
		std::array<Transform::Status, kMaxDigit> digitAnimeStatuses_;
		
		// ロゴ
		std::unique_ptr<BaseDrawObject> logo_;

		// リールタイマー
		YMath::Timer reelTim_;

	private:

		/// <summary>
		/// 桁ごとの色更新
		/// </summary>
		void UpdateDigitColor();
	};
}
