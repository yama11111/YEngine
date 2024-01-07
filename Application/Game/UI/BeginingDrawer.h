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
	class BeginingDrawer
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
		/// アニメーション開始
		/// </summary>
		void PlayAnimation();
	
		/// <summary>
		/// 動作フラグ取得
		/// </summary>
		/// <returns>動作フラグ</returns>
		bool IsAct();

	public:

		/// <summary>
		/// リソース読み込み
		/// </summary>
		static void LoadResource();

	private:
		
		struct StageUI
		{
			Transform trfm;
			std::unique_ptr<UINumber> num;
			std::unique_ptr<DrawObjectForSprite2D> tutorial;
			std::unique_ptr<ConstBufferObject<CBColor>> color;

			bool isTutorial = false;

			YMath::Power scalePow;
			YMath::Ease<float> scaleEas;
		};

		struct CenterRect
		{
			std::unique_ptr<DrawObjectForSprite2D> rect;
			std::unique_ptr<ConstBufferObject<CBColor>> color;

			bool isAct = false;
			YMath::Power scalePow;
			YMath::Ease<float> scaleEas;
		};

		struct MissionRect
		{
			std::unique_ptr<DrawObjectForSprite2D> rect;
			std::unique_ptr<ConstBufferObject<CBColor>> color;

			bool isClear = false;

			bool isAct = false;
			YMath::Power scalePow;
			YMath::Ease<float> scaleEas;
		};

		struct Band
		{
			std::unique_ptr<DrawObjectForSprite2D> band;
			std::unique_ptr<ConstBufferObject<CBColor>> color;

			YMath::Power heightPow;
			YMath::Ease<float> heightEas;
		};

		struct MissionUI
		{
			Transform trfm;

			std::unique_ptr<DrawObjectForSprite2D> star;
			std::unique_ptr<DrawObjectForSprite2D> starFrame;
			
			Transform scoreTrfm;
			std::unique_ptr<UINumber> score;
			std::unique_ptr<DrawObjectForSprite2D> mission;
			
			std::unique_ptr<ConstBufferObject<CBColor>> color;
			
			bool isClear = false;

			YMath::Timer animeTim;
			std::array<YMath::Ease<float>, 2> animePosEass;
		};
	
	private:
		
		// UI
		StageUI ui_;

		// 枠
		Transform rectTrfm_;
		
		CenterRect center_;
		std::array<MissionRect, 3> missions_;
		
		// 帯
		Band band_;

		// ミッション
		std::array<MissionUI, 3> missionUIs_;

		bool isAct_ = false;

		// 生成フラグ
		bool isPop_ = false;
		
		// 消去フラグ
		bool isVanish_ = false;

		// 残存タイマー
		YMath::Timer remainTim_;
	};
}
