#pragma once
#include "PlayerDrawer.h"
#include "HorseDrawer.h"
#include "MapchipManager.h"

#include "Level.h"

#include "UIButton.h"
#include "UILetterBox.h"

namespace YGame
{
	class TitleDrawer
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
		/// 描画
		/// </summary>
		void Draw();
	
	public:

		/// <summary>
		/// 開始アニメーション
		/// </summary>
		void StartAnimation();
		
		/// <summary>
		/// オープニングアニメーション
		/// </summary>
		void OpeningAnimation();
	
	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();
	
	private:

		// タイトル
		std::unique_ptr<DrawObjectForSprite2D> logoObj_;
		std::unique_ptr<DrawObjectForSprite2D> lineObj_;
		std::unique_ptr<DrawObjectForSprite2D> nameObj_;

		// スタート
		std::unique_ptr<DrawObjectForSprite2D> startObj_;
		std::unique_ptr<ConstBufferObject<CBColor>> startColor_;

		// スタートボタン
		std::unique_ptr<UIButton> startButton_;

		// 黒帯
		std::unique_ptr<UILetterBox> letterBox_;

		// プレイヤー
		Transform player_;
		std::unique_ptr<PlayerDrawer> playerDra_;

		// ウマ
		Transform horse_;
		std::unique_ptr<HorseDrawer> horseDra_;

		// レベル
		Level* pLevel_ = nullptr;

		
		std::array<YMath::Timer, 2> openingTims_;
		std::array<YMath::Ease<YMath::Vector3>, 2> titlePosEass_;
		std::array<YMath::Ease<float>, 2> titleScaleEass_;
		SlimeActor slimeActor_;

	private:

		static Sprite2D* spLogoSpr_;
		static Sprite2D* spLineSpr_;
		static Sprite2D* spNameSpr_;
		
		static Sprite2D* spStartSpr_;
		static Sprite2D* spButtonSpr_;
		
		static MapChipManager* spMapChipManager_;

	};
}

