/**
 * @file SpeedLevelDrawer.h
 * @brief スピードレベルを表示するクラス
 * @author Yamanaka Rui
 * @date 2024/01/05
 */

#pragma once
#include "UIDigit.h"
#include "BaseDrawObject.h"
#include "ConstBufferObject.h"
#include "CBColor.h"
#include "ViewProjection.h"
#include "Ease.h"
#include "Timer.h"
#include "Power.h"
#include <array>

namespace YGame
{
	class SpeedLevelDrawer
	{

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		/// <returns>スピードレベル描画クラスポインタ (動的インスタンス)</returns>
		static SpeedLevelDrawer* Create(YMath::Matrix4* pParent, ViewProjection* pVP);

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
		/// スピード変更アニメーション
		/// </summary>
		/// <param name="speed"> : スピードレベル</param>
		void ChangeSpeedAnimation(const uint32_t speed);
	
	private:

		/// <summary>
		/// スピードレベル矢印
		/// </summary>
		struct SpeedLevelDirection
		{
			// 描画用オブジェクト
			std::unique_ptr<BaseDrawObject> obj_;

			// アニメーション数値
			Transform::Status animeStatus_;

			// 移動イージング
			YMath::Ease<float> moveEas_;

			// 移動パワー
			YMath::Power movePower_;
		};

		// 最大スピードレベル
		static const size_t skMaxSpeedLevel_ = 9;

	private:

		// 親トランスフォーム
		Transform transform_;
		
		// 数
		Transform levelTrfm_;
		// レベル
		std::unique_ptr<UIDigit> level_;
		std::unique_ptr<ConstBufferObject<CBColor>> levelColor_;

		// スピードレベルUI
		std::array<SpeedLevelDirection, skMaxSpeedLevel_> levelUIs_;

		// 速度
		uint32_t speedLevel_ = 0;


		// レベルアップしたか
		bool isLevelUpAnimation_ = 0;

		// レベル上昇
		std::unique_ptr<BaseDrawObject> up_;
		std::unique_ptr<ConstBufferObject<CBColor>> upColor_;
		YMath::Power upPow_;
		YMath::Timer upRemainTim_;

	};
}
