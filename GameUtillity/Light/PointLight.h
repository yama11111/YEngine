#pragma once
#include "Vector3.h"

namespace YGame
{
	class PointLight
	{
	public:
		// 定数バッファデータ構造体 (光)
		struct CBData
		{
			YMath::Vector3 lightPos_; // 座標
			float pad1_; // パディング
			YMath::Vector3 lightColor_; // 色
			float pad2_; // パディング
			YMath::Vector3 lightAtten_; // 距離減衰係数
			float active_; // 動作フラグ
		};
	private:
		// 座標
		YMath::Vector3 pos_;
		// 色
		YMath::Vector3 color_;
		// 距離減衰係数
		YMath::Vector3 atten_;
		// 有効フラグ
		bool isAct_ = false;
	public:
		// 初期化
		void Initialize(const YMath::Vector3& pos, const YMath::Vector3& color = { 1.0f,1.0f,1.0f }, 
			const YMath::Vector3& atten = { 0.005f,0.005f,0.005f });
	public:
		// 座標取得
		YMath::Vector3 Pos() { return pos_; }
		// 座標設定
		void SetPos(const YMath::Vector3& pos);
		// 色取得
		YMath::Vector3 Color() { return color_; }
		// 色設定 (0.0f ～ 1.0f)
		void SetColor(const YMath::Vector3& color);
		// 色設定 (0 ～ 255)
		void SetColor(const unsigned int R, const unsigned int G, const unsigned int B);
		// 距離減衰係数取得
		YMath::Vector3 Atten() { return atten_; }
		// 距離減衰係数設定
		void SetAtten(const YMath::Vector3& atten);
		// 有効か
		bool IsActive() { return isAct_; }
		// 有効フラグ設定
		void SetActive(const bool isAct) { isAct_ = isAct; }
	public:
		PointLight();
		~PointLight() = default;
	};
}
