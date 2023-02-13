#pragma once
#include "Vector3.h"
#include "Vector2.h"

namespace YGame
{
	class SpotLight
	{
	public:
		// 定数バッファデータ構造体 (光)
		struct CBData
		{
			YMath::Vector3 lightPos_; // 座標
			float pad1_; // パディング
			YMath::Vector3 lightVec_; // 向き
			float pad2_; // パディング
			YMath::Vector3 lightColor_; // 色
			float pad3_; // パディング
			YMath::Vector3 lightAtten_; // 距離減衰係数
			float pad4_; // パディング
			float lightStartFactorAngleCos_; // 減衰開始角度
			float lightEndFactorAngleCos_; // 減衰終了角度
			float active_; // 動作フラグ
			float pad5_; // パディング
		};
	private:
		// 座標
		YMath::Vector3 pos_;
		// 向き
		YMath::Vector3 direction_;
		// 色
		YMath::Vector3 color_;
		// 距離減衰係数
		YMath::Vector3 atten_;
		// 減衰開始角度
		float startFactorAngleCos_ = 0.0f;
		// 減衰終了角度
		float endFactorAngleCos_ = 0.0f;
		// 有効フラグ
		bool isAct_ = false;
	public:
		// 初期化
		void Initialize(const YMath::Vector3& pos, const YMath::Vector3& direction = { 0.0f,-1.0f,0.0f },
			const YMath::Vector3& color = { 1.0f,1.0f,1.0f }, const YMath::Vector3& atten = { 0.005f,0.005f,0.005f },
			const float startFactorAngleCos = 0.5f, const float endFactorAngleCos = 0.2f);
	public:
		// 座標取得
		YMath::Vector3 Pos() { return pos_; }
		// 座標設定
		void SetPos(const YMath::Vector3& pos);
		// 向き取得
		YMath::Vector3 Direction() { return direction_; }
		// 向き
		void SetDirection(const YMath::Vector3& direciton);
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
		// 減衰開始角度取得
		float StartFactorAngleCos() { return startFactorAngleCos_; }
		// 減衰開始角度設定
		void SetStartFactorAngleCos(const float startFactorAngleCos);
		// 減衰終了角度取得
		float EndFactorAngleCos() { return startFactorAngleCos_; }
		// 減衰終了角度設定
		void SetEndFactorAngleCos(const float endFactorAngleCos);
		// 有効か
		bool IsActive() { return isAct_; }
		// 有効フラグ設定
		void SetActive(const bool isAct) { isAct_ = isAct; }
	public:
		SpotLight();
		~SpotLight() = default;
	};
}
