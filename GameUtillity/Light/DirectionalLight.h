#pragma once
#include "Vector3.h"

namespace YGame
{
	class DirectionalLight
	{
	public:
		// 定数バッファデータ構造体 (光)
		struct CBData
		{
			YMath::Vector3 lightVec_; // 向き
			float pad_; // パディング
			YMath::Vector3 lightColor_; // 色
			float active_; // 動作フラグ
		};
	private:
		// 向き
		YMath::Vector3 direction_;
		// 色
		YMath::Vector3 color_;
		// 有効フラグ
		bool isAct_ = false;
	public:
		// 初期化
		void Initialize(const YMath::Vector3& direction, const YMath::Vector3& color = { 1.0f,1.0f,1.0f });
	public:
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
		// 有効か
		bool IsActive() { return isAct_; }
		// 有効フラグ設定
		void SetActive(const bool isAct) { isAct_ = isAct; }
	public:
		DirectionalLight();
		~DirectionalLight() = default;
	};
}

