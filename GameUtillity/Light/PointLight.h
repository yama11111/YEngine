#pragma once
#include "Vec3.h"

namespace YGame
{
	class PointLight
	{
	public:
		// 定数バッファデータ構造体 (光)
		struct CBData
		{
			YMath::Vec3 lightPos_; // 座標
			float pad1_; // パディング
			YMath::Vec3 lightColor_; // 色
			float pad2_; // パディング
			YMath::Vec3 lightAtten_; // 距離減衰係数
			float active_; // 動作フラグ
		};
	private:
		// 座標
		YMath::Vec3 pos_;
		// 色
		YMath::Vec3 color_;
		// 距離減衰係数
		YMath::Vec3 atten_;
		// 有効フラグ
		bool isAct_ = false;
	public:
		// 初期化
		void Initialize(const YMath::Vec3& pos, const YMath::Vec3& color = { 1.0f,1.0f,1.0f }, 
			const YMath::Vec3& atten = { 0.005f,0.005f,0.005f });
	public:
		// 座標取得
		YMath::Vec3 Pos() { return pos_; }
		// 座標設定
		void SetPos(const YMath::Vec3& pos);
		// 色取得
		YMath::Vec3 Color() { return color_; }
		// 色設定 (0.0f ～ 1.0f)
		void SetColor(const YMath::Vec3& color);
		// 色設定 (0 ～ 255)
		void SetColor(const unsigned int R, const unsigned int G, const unsigned int B);
		// 距離減衰係数取得
		YMath::Vec3 Atten() { return atten_; }
		// 距離減衰係数設定
		void SetAtten(const YMath::Vec3& atten);
		// 有効か
		bool IsActive() { return isAct_; }
		// 有効フラグ設定
		void SetActive(const bool isAct) { isAct_ = isAct; }
	public:
		PointLight();
		~PointLight() = default;
	};
}
