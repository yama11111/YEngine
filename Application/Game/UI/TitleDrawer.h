#pragma once
#include "DrawObjectForSprite2D.h"
#include "CBColor.h"
#include "UIButton.h"

#include "Ease.h"
#include "Timer.h"
#include "Power.h"

#include <array>

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

		struct TitleChara
		{
			std::unique_ptr<DrawObjectForSprite2D> chara;
			std::unique_ptr<ConstBufferObject<CBColor>> color;

			YMath::Timer animeTim;
			YMath::Ease<float> posEas;
		};

		struct Band
		{
			std::unique_ptr<DrawObjectForSprite2D> band;
			std::unique_ptr<ConstBufferObject<CBColor>> color;
			
			YMath::Timer scaleTim;
			YMath::Ease<YMath::Vector3> scaleEas;
		};
	
	private:

		std::array<TitleChara, 6> titleLogo_;
		std::array<Band, 2> bands_;

		std::unique_ptr<DrawObjectForSprite2D> start_;
		std::unique_ptr<ConstBufferObject<CBColor>> startColor_;
		
		Transform startButtonTrfm_;
		std::unique_ptr<UIButton> startButton_;

		std::unique_ptr<DrawObjectForSprite2D> circle_;
		std::unique_ptr<ConstBufferObject<CBColor>> circleColor_;
		YMath::Timer circleScaleTim_;
		YMath::Ease<float> circleScaleEas_;
		
		std::unique_ptr<DrawObjectForSprite2D> curten_;
		std::unique_ptr<ConstBufferObject<CBColor>> curtenColor_;
		YMath::Timer curtenAlphaTim_;

	private:

		static std::array<Sprite2D*, 6> spTitleCharaSprs_;

		static Sprite2D* spStartSpr_;
		
		static Sprite2D* spButtonSpr_;
		
		static Sprite2D* spCircleSpr_;
		
		static Sprite2D* spWhiteSpr_;
	
	private:

		void UpdateAnimeFlag();
	
	};
}

