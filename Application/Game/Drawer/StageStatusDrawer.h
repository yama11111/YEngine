#pragma once
#include "DrawObjectForSprite2D.h"
#include "CBColor.h"
#include "UINumber.h"

#include "Ease.h"
#include "Timer.h"
#include "Power.h"

#include <array>

namespace YGame
{
	class StageStatusDrawer
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize(
			const uint32_t number,
			const bool isTutorial,
			const std::array<bool, 3>& isMissionClear);

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
		/// 現れる
		/// </summary>
		void AppearAnimation();

		/// <summary>
		/// 消える
		/// </summary>
		void DisappearAnimation();

	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

	private:

		struct Band
		{
			std::unique_ptr<DrawObjectForSprite2D> band;
			std::unique_ptr<ConstBufferObject<CBColor>> color;

			bool isAct = false;
			YMath::Power posPow;
			YMath::Ease<float> posEas;
		};

		struct Mission
		{
			Transform trfm;

			std::unique_ptr<DrawObjectForSprite2D> star;
			std::unique_ptr<DrawObjectForSprite2D> starFrame;
			std::unique_ptr<DrawObjectForSprite2D> mission;
			std::unique_ptr<ConstBufferObject<CBColor>> color;

			bool isAct = false;
			YMath::Power posPow;

			bool isClear = false;
		};

	private:

		Transform titleTrfm_;

		std::array<Band, 2> bands_;

		std::unique_ptr<DrawObjectForSprite2D> logo_;

		Transform numberTrfm_;
		std::unique_ptr<UINumber> number_;

		std::unique_ptr<DrawObjectForSprite2D> tutorialLogo_;
		std::unique_ptr<DrawObjectForSprite2D> tutorialMark_;

		std::unique_ptr<ConstBufferObject<CBColor>> color_;

		std::array<Mission, 3> missions_;

		bool isTutorial_ = false;
		bool isAct_ = false;

		YMath::Power titlePosPow_;
		YMath::Ease<float> titlePosEas_;

		YMath::Ease<float> missionPosEas_;

		YMath::Power alphaPow_;

	private:

		static Sprite2D* spStageLogoSpr_;
		static Sprite2D* spBandSpr_;

		static Sprite2D* spStarSpr_;
		static Sprite2D* spStarFrameSpr_;

		static Sprite2D* spMissionSpr_;

		static Sprite2D* spTutorialLogoSpr_;
		static Sprite2D* spTutorialMarkSpr_;

	private:

		void UpdateActFlag();

	};
}
