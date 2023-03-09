#pragma once
#include "ConstBuffer.h"
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
		};
	private:
		// 色
		YMath::Vector4 color_;
		// 定数バッファ(マテリアル1)
		YDX::ConstBuffer<CBData> cBuff_;
	public:
		// 生成
		static Color* Create(const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f });
	public:
		// 初期化
		void Initialize(const YMath::Vector4& color = { 1.0f,1.0f,1.0f,1.0f });
		// 描画前コマンド
		void SetDrawCommand(const UINT rootParamIndex);
	public:
		// RGBA取得
		YMath::Vector4 GetRGBA() const { return color_; }
		// 色設定 (0.0f ～ 1.0f)
		void SetRGBA(const YMath::Vector4& color);
		// 色設定 (0 ～ 255)
		void SetRGBA(const UINT R, const UINT G, const UINT B, const UINT A);
	private:
		Color();
	public:
		~Color() = default;
	};
}

