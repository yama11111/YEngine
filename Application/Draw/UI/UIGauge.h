/**
 * @file UIGauge.h
 * @brief UI用のゲージの機能を持ったクラス
 * @author Yamanaka Rui
 * @date 2024/01/05
 */

#pragma once
#include "BaseDrawObject.h"

namespace YGame
{
	class UIGauge
	{

	public:

		/// <summary>
		/// 動的インスタンス生成
		/// </summary>
		/// <param name="obj"> : オブジェクト (動的インスタンス)</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		/// <returns>動的インスタンス</returns>
		static UIGauge* Create(BaseDrawObject* obj, const bool isClearWhenTransition = true);

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="obj"> : オブジェクト (動的インスタンス)</param>
		/// <param name="isClearWhenTransition"> : 遷移時クリアするか</param>
		virtual void Initialize(BaseDrawObject* obj, const bool isClearWhenTransition = true) = 0;

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update() = 0;

		/// <summary>
		/// 描画
		/// </summary>
		/// <param name="shaderTag"> : シェーダータグ</param>
		/// <param name="priority"> : 描画優先度</param>
		virtual void Draw(const std::string& shaderTag, const size_t priority) = 0;

	public:

		/// <summary>
		/// 変更
		/// </summary>
		/// <param name="ratio"> : 変更後の割合</param>
		/// <param name="frame"> : 時間</param>
		/// <param name="exponent"> : 指数(緩急)</param>
		virtual void Change(const float ratio, const uint32_t frame, const float exponent) = 0;

	public:

		/// <summary>
		/// 親ポインタ設定
		/// </summary>
		/// <param name="pParent"> : 親ポインタ</param>
		virtual void SetParent(YMath::Matrix4* pParent) = 0;

		/// <summary>
		/// 割合設定
		/// </summary>
		/// <param name="ratio"></param>
		virtual void SetRatio(const float ratio) = 0;

	public:

		UIGauge() = default;

		virtual ~UIGauge() = default;

	};
}
