#pragma once
#include "ConstBuffer.h"
#include "Vec3.h"

namespace YGame
{
	class Light
	{
	private:
		// 定数バッファデータ構造体 (光)
		struct CBData
		{
			YMath::Vec3 lightVec_;	 // 向き
			float pad;				 // パディング
			YMath::Vec3 lightColor_; // 色
		};
	private:
		// 向き
		YMath::Vec3 direction_;
		// 色
		YMath::Vec3 color_;
		// 定数バッファ(光)
		YDX::ConstBuffer<CBData> cBuff_;
	public:
		// 初期化
		void Initialize(const YMath::Vec3& direction, const YMath::Vec3& color = { 1.0f,1.0f,1.0f });
		// 描画前コマンド
		void SetDrawCommand(const UINT rootParamIndex);
	public:
		// 向き
		void SetDirection(const YMath::Vec3& direciton);
		// 色設定 (0.0f ～ 1.0f)
		void SetColor(const YMath::Vec3& color);
		// 色設定 (0 ～ 255)
		void SetColor(const UINT R, const UINT G, const UINT B);
	public:
		Light();
		~Light() = default;
	};
}
