#pragma once
#include "ConstBuffer.h"
#include "Vec4.h"

namespace YGame
{
	class Color
	{
	private:
		// 定数バッファデータ構造体 (色)
		struct CBData
		{
			YMath::Vec4 color_; // 色 (RGBA)
		};
	private:
		// 色
		YMath::Vec4 color_;
		// 定数バッファ(マテリアル1)
		YDX::ConstBuffer<CBData> cBuff_;
	public:
		// 初期化
		void Initialize(const YMath::Vec4& color = { 1.0f,1.0f,1.0f,1.0f });
		// 描画前コマンド
		void SetDrawCommand(const UINT rootParamIndex);
	public:
		// 色設定 (0.0f ～ 1.0f)
		void SetRGBA(const YMath::Vec4& color);
		// 色設定 (0 ～ 255)
		void SetRGBA(const UINT R, const UINT G, const UINT B, const UINT A);
	public:
		Color();
		~Color() = default;
	};
}

