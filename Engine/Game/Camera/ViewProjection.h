#pragma once
#include "Vector3.h"
#include "Matrix4.h"

namespace YGame
{
	// ビュープロジェクション
	struct ViewProjection
	{
	
	public:
		
		// 視点
		YMath::Vector3 eye_;
		
		// 注視点
		YMath::Vector3 target_;
		
		// 上方向ベクトル
		YMath::Vector3 up_;
		
		// ビュー行列
		YMath::Matrix4 view_;
		
		// プロジェクション行列
		YMath::Matrix4 pro_;
	
	public:
		
		// 設定用ステータス(視点、注視点、上方向ベクトル)
		struct Status
		{

		public:

			// 視点
			YMath::Vector3 eye_;
			
			// 注視点
			YMath::Vector3 target_;
			
			// 上方向ベクトル
			YMath::Vector3 up_;

		public:

			// デフォルト値
			static Status Default();
		};

	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : 初期化用ステータス</param>
		/// <param name="------------------------------------"></param>
		/// <param name="status.eye_"> : 視点</param>
		/// <param name="status.target_"> : 注視点</param>
		/// <param name="status.up_"> : 上方向ベクトル</param>
		void Initialize(const Status& status = Status::Default());
		
		// ビュー変換 + プロジェクション変換
		void UpdateMatrix();
	
	public:
		
		// コンストラクタ
		ViewProjection();
	
	};
}