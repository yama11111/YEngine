#pragma once
#include "UIGauge.h"
#include "DrawObjectForSprite2D.h"
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
		/// <param name="shaderTag"> : シェーダータグ</param>
		/// <param name="drawPriority"> : 描画優先度</param>
		/// <returns>スコア描画クラスポインタ (動的インスタンス)</returns>
		static HPGaugeDrawer* Create(
			YMath::Matrix4* pParent, 
			const std::string& shaderTag, 
			const size_t drawPriority);	
	
		/// <summary>
		/// 静的初期化
		/// </summary>
		static void LoadResource();

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		void Initialize(YMath::Matrix4* pParent);
		
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
	
	private:

		// 値
		uint32_t value_ = 0;
		// 最大値
		uint32_t maxValue_ = 0;

		// 親ポインタ
		YMath::Matrix4* pParent_ = nullptr;

		// ゲージ
		std::unique_ptr<UIGauge> gauge_;
		std::unique_ptr<ConstBufferObject<CBColor>> gaugeColor_;
		// プラスゲージ
		std::unique_ptr<UIGauge> gaugeMinus_;
		std::unique_ptr<ConstBufferObject<CBColor>> gaugeMinusColor_;
		// マイナスゲージ
		std::unique_ptr<UIGauge> gaugePlus_;
		std::unique_ptr<ConstBufferObject<CBColor>> gaugePlusColor_;
		
		// 背景
		std::unique_ptr<DrawObjectForSprite2D> back_;
		std::unique_ptr<ConstBufferObject<CBColor>> backColor_;
		// 枠
		std::unique_ptr<DrawObjectForSprite2D> frame_;
		std::unique_ptr<ConstBufferObject<CBColor>> frameColor_;

		// シェーダータグ
		std::string shaderTag_{};
		// 描画優先度
		size_t drawPriority_ = 0;
	
	private:

		/// <summary>
		/// 割合取得
		/// </summary>
		/// <returns>割合</returns>
		const float ValueRatio() const;
	
	};
}
