#pragma once
#include "DrawObjectForSprite3D.h"
#include "CBColor.h"
#include "UINumber.h"

#include "Ease.h"
#include "Timer.h"
#include "Power.h"

#include <array>

namespace YGame
{
	class StageDrawer
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize(
			YMath::Matrix4* pParent,
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
		/// 生成アニメーション
		/// </summary>
		void PopAnimation();
		
		/// <summary>
		/// 選択アニメーション
		/// </summary>
		void SelectAnimation();

		/// <summary>
		/// 開放アニメーション
		/// </summary>
		void ReleseAnimation();
	
	public:

		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

		/// <summary>
		/// ビュープロジェクションポインタ設定
		/// </summary>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		static void SetViewProjection(ViewProjection* pVP);

	private:

		struct MissionFrame
		{
			bool isClear = false;
			std::unique_ptr<DrawObjectForSprite3D> frame;
			std::unique_ptr<ConstBufferObject<CBColor>> color;

			bool isPop = false;
			YMath::Power popScalePow;
			YMath::Ease<float> popScaleEas;
			
			bool isSelect = false;
			YMath::Power selectScalePow;
			YMath::Ease<float> selectScaleEas;
		};
	
	private:

		Transform trfm_;

		std::unique_ptr<DrawObjectForSprite3D> centerFrame_;
		std::unique_ptr<ConstBufferObject<CBColor>> color_;
		
		Transform uiTrfm_;
		std::unique_ptr<UINumber> uiNum_;
		std::unique_ptr<DrawObjectForSprite3D> uiTutorial_;
		bool isTutorial_ = false;

		bool isPop_ = false;
		YMath::Power popScalePow_;
		YMath::Ease<float> popScaleEas_;

		bool isSelect_ = false;
		YMath::Power selectScalePow_;
		YMath::Ease<float> selectScaleEas_;
		
		std::array<MissionFrame, 3> missionFrames_;

	private:

		static ViewProjection* spVP_;

		static Sprite3D* spFrameSpr_;
		
		static Sprite3D* spTutorialSpr_;
	
	private:

		void UpdateActFlag();

	};
}
