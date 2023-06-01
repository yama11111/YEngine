#pragma once
#include "ConstBuffer.h"
#include "Vector3.h"
#include "Vector4.h"

namespace YGame
{
	class CBColor
	{
	
	public:

		// 定数バッファデータ構造体 (色)
		struct CBData
		{
			YMath::Vector4 baseColor_; // 色 (RGBA)
			YMath::Vector4 texColorRate_; // テクスチャの色の割合
		};
		
	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="color"> : 色</param>
		/// <param name="originalRate"> : 元の色の割合</param>
		/// <param name="isMutable"> : シーン遷移時に開放するか</param>
		/// <returns>動的インスタンス (newされたもの)</returns>
		static CBColor* Create(
			const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f },
			const YMath::Vector4& originalRate = { 1.0f,1.0f,1.0f,1.0f },
			const bool isMutable = true);

	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="baseColor"> : 色</param>
		/// <param name="texColorRate"> : テクスチャの色の割合</param>
		void Initialize(
			const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f },
			const YMath::Vector4& originalRate = { 1.0f,1.0f,1.0f,1.0f });


		/// <summary>
		/// 描画前コマンド
		/// </summary>
		/// <param name="rootParamIndex"> : ルートパラメータ番号</param>
		void SetDrawCommand(const UINT rootParamIndex);

	public:

		/// <summary>
		/// RGBA取得
		/// </summary>
		/// <returns>RGBA</returns>
		YMath::Vector4 GetRGBA() const { return baseColor_; }
		

		/// <summary>
		/// 色 + アルファ値設定 (0.0f ～ 1.0f)
		/// </summary>
		/// <param name="color"></param>
		void SetRGBA(const YMath::Vector4& color);
		
		/// <summary>
		/// 色設定 (0.0f ～ 1.0f)
		/// </summary>
		/// <param name="color"> : RGB</param>
		void SetRGB(const YMath::Vector3& color);
		
		/// <summary>
		/// アルファ値設定 (0.0f ～ 1.0f)
		/// </summary>
		/// <param name="alpha"> : アルファ値</param>
		void SetAlpha(const float alpha);

	public:
		
		/// <summary>
		/// テクスチャの色の割合取得
		/// </summary>
		/// <returns>RGBAの割合</returns>
		YMath::Vector4 GetTexColorRate() const { return texColorRate_; }
		

		/// <summary>
		/// 色 + アルファ値の割合設定 (0.0f ～ 1.0f)
		/// </summary>
		/// <param name="colorRate"> : RGBAの割合</param>
		void SetTexColorRateRGBA(const YMath::Vector4& colorRate);

		/// <summary>
		/// 色の割合設定 (0.0f ～ 1.0f)
		/// </summary>
		/// <param name="colorRate"> : RGBの割合</param>
		void SetTexColorRateRGB(const YMath::Vector3& colorRate);

		/// <summary>
		/// アルファ値設定 (0.0f ～ 1.0f)
		/// </summary>
		/// <param name="alphaRate"> : アルファ値の割合</param>
		void SetTexColorRateAlpha(const float alphaRate);

	private:

		CBColor() = default;

	public:

		~CBColor() = default;

	private:

		// 定数バッファ(色)
		YDX::ConstBuffer<CBData> cBuff_;

		// 色
		YMath::Vector4 baseColor_ = { 1.0f,1.0f,1.0f,1.0f };
		
		// 元の色の割合
		YMath::Vector4 texColorRate_ = { 1.0f,1.0f,1.0f,1.0f };

	};
}

