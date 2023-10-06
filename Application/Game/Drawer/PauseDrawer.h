#pragma once
#include "DrawObjectForSprite2D.h"
#include "CBColor.h"
#include "Ease.h"
#include "Power.h"
#include <array>

namespace YGame
{
	class PauseDrawer
	{

	public:

		// 選択
		enum class Selection : size_t
		{
			Resume, // 戻る
			ReStart, // リスタート
			Change, // 遷移
			End,
		};

		// 選択肢の数
		static const size_t kSelectionNum = static_cast<size_t>(Selection::End);

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

	public:

		/// <summary>
		/// 起動アニメーション
		/// </summary>
		void BootAnimation();
		
		/// <summary>
		/// 停止アニメーション
		/// </summary>
		void ShutdownAnimation();

		/// <summary>
		/// 選択肢設定
		/// </summary>
		/// <param name="select"> : 選択</param>
		void SetSelection(const Selection select);

	public:

		/// <summary>
		/// リソース読み込み
		/// </summary>
		static void LoadResource();

	private:
		
		// 選択肢構造体
		struct SelectionObject
		{
			// オブジェクト
			std::unique_ptr<DrawObjectForSprite2D> obj_;
			std::unique_ptr<ConstBufferObject<CBColor>> color_;

			// 演出用
			bool isActPos_ = false;
			YMath::Power posXPow_;
			YMath::Ease<float> posXEas_;
			YMath::Power scalePow_;
		};
	
	private:

		// 選択
		Selection selection_ = Selection::Resume;

		// アニメーション
		bool isAct_ = false;
		YMath::Power animePow_;

		// ポーズロゴ
		std::unique_ptr<DrawObjectForSprite2D> pauseLogo_;
		YMath::Ease<float> pauseLogoPosXEas_;
		
		// 選択肢
		std::array<SelectionObject, kSelectionNum> selectionObjs_;
		YMath::Ease<YMath::Vector3> selectScaleEas_;
		
		// 境界線
		std::unique_ptr<DrawObjectForSprite2D> border_;
		YMath::Ease<float> borderScaleYEas_;

		// 背景カーテン
		std::unique_ptr<DrawObjectForSprite2D> curten_;
		std::unique_ptr<ConstBufferObject<CBColor>> curtenColor_;
		YMath::Power curtenAlphaPow_;
		YMath::Ease<float> curtenAlphaEas_;

	private:

		// ポーズロゴスプライト
		static Sprite2D* spPauseLogo_;

		// 選択肢ロゴスプライト
		static std::array<Sprite2D*, kSelectionNum> spSelectionSprites_;
		
		// 境界線スプライト
		static Sprite2D* spBorder_;
		
		// カーテンスプライト
		static Sprite2D* spCurten_;

	private:

		/// <summary>
		/// 伝播
		/// </summary>
		void PropagateSelection(const size_t index);
	};
}

