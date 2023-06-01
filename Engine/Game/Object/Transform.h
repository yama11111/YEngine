#pragma once
#include "Vector3.h"
#include "Matrix4.h"

namespace YGame
{
	// トランスフォーム (位置、回転、大きさ)
	struct Transform
	{
	
	public:
		
		// 位置
		YMath::Vector3 pos_;
		
		// 回転
		YMath::Vector3 rota_;
		
		// 大きさ
		YMath::Vector3 scale_;
		
		// 行列
		YMath::Matrix4 m_;
		
		// 親行列
		YMath::Matrix4* parent_;
	
	public:
		
		// 設定用ステータス
		struct Status
		{

		public:

			// 位置
			YMath::Vector3 pos_;
			
			// 回転
			YMath::Vector3 rota_;
			
			// 大きさ
			YMath::Vector3 scale_;

		public:

			// デフォルト値
			static Status Default();

		};

	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : 設定用ステータス</param>
		/// <param name="(Vector3) status.pos_"> : 位置</param>
		/// <param name="(Vector3) status.rota_"> : 回転</param>
		/// <param name="(Vector3) status.scale_"> : 大きさ</param>
		void Initialize(const Status& status = Status::Default());
		
		/// <summary>
		/// アフィン変換
		/// </summary>
		void UpdateMatrix();
		
		/// <summary>
		/// アフィン変換 (位置、回転、大きさ を加算したオブジェクトで行列計算)
		/// </summary>
		/// <param name="status"> : 設定用ステータス</param>
		/// <param name="(Vector3) status.pos_"> : 位置</param>
		/// <param name="(Vector3) status.rota_"> : 回転</param>
		/// <param name="(Vector3) status.scale_"> : 大きさ</param>
		void UpdateMatrix(const Status& status);
	
	public:
		
		Transform();
		
		virtual ~Transform() = default;
	};
}
