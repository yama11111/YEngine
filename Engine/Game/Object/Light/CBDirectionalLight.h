#pragma once
#include "Vector3.h"

namespace YGame
{
	class CBDirectionalLight
	{
	
	public:
		
		// 定数バッファデータ構造体 (光)
		struct Data
		{
			YMath::Vector3 lightVec_; // 向き
			float pad_;
			YMath::Vector3 lightColor_; // 色
			float active_; // 動作フラグ
		};
	
	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="direction"> : 向き</param>
		/// <param name="color"> : 色</param>
		void Initialize(const YMath::Vector3& direction, const YMath::Vector3& color = { 1.0f,1.0f,1.0f });

		/// <summary>
		/// 定数データ取得
		/// </summary>
		/// <returns>定数データ</returns>
		Data GetData() const;
	
	public:
		
		// 向き取得
		YMath::Vector3 Direction() { return direction_; }
		
		// 向き
		void SetDirection(const YMath::Vector3& direciton);
		
		// 色取得
		YMath::Vector3 Color() { return color_; }
		
		// 色設定 (0.0f ～ 1.0f)
		void SetColor(const YMath::Vector3& color);
		
		// 有効か
		bool IsActive() { return isAct_; }
		
		// 有効フラグ設定
		void SetActive(const bool isAct) { isAct_ = isAct; }
	
	public:
		
		CBDirectionalLight() = default;
		
		~CBDirectionalLight() = default;

	private:
		
		// 向き
		YMath::Vector3 direction_ = { 1.0f,1.0f,1.0f };
		
		// 色
		YMath::Vector3 color_ = { 1.0f,1.0f,1.0f };
		
		// 有効フラグ
		bool isAct_ = false;
	
	};
}

