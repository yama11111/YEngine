#pragma once
#include "ConstBuffer.h"
#include "Vector3.h"
#include "Vector4.h"

namespace YGame
{
	class Color
	{
	public:

		// 定数バッファデータ構造体 (色)
		struct CBData
		{
			YMath::Vector4 color_; // 色 (RGBA)
			YMath::Vector4 originalRate_; // 元の色の割合
		};

	private:

		// 色
		YMath::Vector4 color_;
		
		// 元の色の割合
		YMath::Vector4 originalRate_;
		
		// 定数バッファ(マテリアル1)
		YDX::ConstBuffer<CBData> cBuff_;

	public:

		/// <summary>
		/// 生成
		/// </summary>
		/// <param name="color"> : 色</param>
		/// <param name="originalRate"> : 元の色の割合</param>
		/// <param name="isMutable"> : シーン遷移時に開放するか</param>
		/// <returns></returns>
		static Color* Create(
			const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f },
			const YMath::Vector4& originalRate = { 1.0f,1.0f,1.0f,1.0f },
			const bool isMutable = true
		);

	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="color"> : 色</param>
		/// <param name="originalRate"> : 元の色の割合</param>
		void Initialize(
			const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f },
			const YMath::Vector4& originalRate = { 1.0f,1.0f,1.0f,1.0f }
		);

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
		YMath::Vector4 GetRGBA() const { return color_; }
		

		/// <summary>
		/// 色 + アルファ値設定 (0.0f ～ 1.0f)
		/// </summary>
		/// <param name="color"></param>
		void SetRGBA(const YMath::Vector4& color);
		
		/// <summary>
		/// 色 + アルファ値設定 (0 ～ 255)
		/// </summary>
		/// <param name="R"> : 赤</param>
		/// <param name="G"> : 緑</param>
		/// <param name="B"> : 青</param>
		/// <param name="A"> : アルファ値</param>
		void SetRGBA(const UINT R, const UINT G, const UINT B, const UINT A);
		
		/// <summary>
		/// 色設定 (0.0f ～ 1.0f)
		/// </summary>
		/// <param name="color"> : RGB</param>
		void SetRGB(const YMath::Vector3& color);
		
		/// <summary>
		/// 色設定 (0 ～ 255)
		/// </summary>
		/// <param name="R"> : 赤</param>
		/// <param name="G"> : 緑</param>
		/// <param name="B"> : 青</param>
		void SetRGB(const UINT R, const UINT G, const UINT B);
		
		/// <summary>
		/// アルファ値設定 (0.0f ～ 1.0f)
		/// </summary>
		/// <param name="alpha"> : アルファ値</param>
		void SetAlpha(const float alpha);
		
		/// <summary>
		/// アルファ値設定 (0 ～ 255)
		/// </summary>
		/// <param name="alpha"> : アルファ値</param>
		void SetAlpha(const UINT alpha);

	public:
		
		/// <summary>
		/// 元の色の割合取得
		/// </summary>
		/// <returns>RGBAの割合</returns>
		YMath::Vector4 GetOriginalRate() const { return originalRate_; }
		

		/// <summary>
		/// 色 + アルファ値の割合設定 (0.0f ～ 1.0f)
		/// </summary>
		/// <param name="color"> : RGBAの割合</param>
		void SetOriginalRateRGBA(const YMath::Vector4& color);
		
		/// <summary>
		/// 色 + アルファ値の割合設定 (0 ～ 255)
		/// </summary>
		/// <param name="R"> : 赤の割合</param>
		/// <param name="G"> : 緑の割合</param>
		/// <param name="B"> : 青の割合</param>
		/// <param name="A"> : アルファ値の割合</param>
		void SetOriginalRateRGBA(const UINT R, const UINT G, const UINT B, const UINT A);
		
		/// <summary>
		/// 色の割合設定 (0.0f ～ 1.0f)
		/// </summary>
		/// <param name="color"> : RGBの割合</param>
		void SetOriginalRateRGB(const YMath::Vector3& color);
		
		/// <summary>
		/// 色の割合設定 (0 ～ 255)
		/// </summary>
		/// <param name="R"> : 赤の割合</param>
		/// <param name="G"> : 緑の割合</param>
		/// <param name="B"> : 青の割合</param>
		void SetOriginalRateRGB(const UINT R, const UINT G, const UINT B);
		
		/// <summary>
		/// アルファ値設定 (0.0f ～ 1.0f)
		/// </summary>
		/// <param name="alpha"> : アルファ値の割合</param>
		void SetOriginalRateAlpha(const float alpha);
		
		/// <summary>
		/// アルファ値設定 (0 ～ 255)
		/// </summary>
		/// <param name="alpha"> : アルファ値の割合</param>
		void SetOriginalRateAlpha(const UINT alpha);

	private:

		Color();

	public:

		~Color() = default;

	};
}

