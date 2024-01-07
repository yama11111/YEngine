/**
 * @file HPGaugeDrawer.h
 * @brief HPゲージを表示するクラス
 * @author Yamanaka Rui
 * @date 2024/01/05
 */

#pragma once
#include "UIGauge.h"
#include "ViewProjection.h"
#include "ConstBufferObject.h"
#include "CBColor.h"

namespace YGame
{
	class HPGaugeDrawer
	{
	
	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		/// <param name="pVP"> : ビュープロジェクションポインタ</param>
		/// <returns>HPゲージ描画クラスポインタ (動的インスタンス)</returns>
		static HPGaugeDrawer* Create(YMath::Matrix4* pParent, ViewProjection* pVP);
	
		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
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
		/// HP変更アニメーション
		/// </summary>
		/// <param name="value"> : 値</param>
		/// <param name="maxValue"> : 最大値</param>
		void ChangeHPAnimation(const uint32_t value, const uint32_t maxValue);
	
	private:
		
		// 値
		uint32_t value_ = 0;
		// 最大値
		uint32_t maxValue_ = 0;

		// トランスフォーム
		Transform transform_;

		// ゲージ
		std::unique_ptr<UIGauge> gauge_;
		std::unique_ptr<ConstBufferObject<CBColor>> gaugeColor_;
		
		// プラスゲージ
		std::unique_ptr<UIGauge> gaugeMinus_;
		std::unique_ptr<ConstBufferObject<CBColor>> gaugeMinusColor_;
		
		// マイナスゲージ
		std::unique_ptr<UIGauge> gaugePlus_;
		std::unique_ptr<ConstBufferObject<CBColor>> gaugePlusColor_;
	
	private:

		/// <summary>
		/// 値設定
		/// </summary>
		/// <param name="value"> : 値</param>
		/// <param name="isDecrease"> : 減少フラグ</param>
		void ChangeValueAnimation(const uint32_t value, const bool isDecrease);

		/// <summary>
		/// 最大値設定
		/// </summary>
		/// <param name="maxValue"> : 最大値</param>
		/// <param name="isDecrease"> : 減少フラグ</param>
		void ChangeMaxValueAnimation(const uint32_t maxValue, const bool isDecrease);

		/// <summary>
		/// 割合取得
		/// </summary>
		/// <returns>割合</returns>
		const float ValueRatio() const;
	
	};
}
