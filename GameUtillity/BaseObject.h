#pragma once
#include "Vector3.h"
#include "Matrix4.h"

namespace YGame
{
	// オブジェクト基底クラス
	class BaseObject
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
		// 設定用ステータス(位置、回転、大きさ)
		struct Status
		{
			YMath::Vector3 pos_ = { 0.0f, 0.0f, 0.0f };
			YMath::Vector3 rota_ = { 0.0f, 0.0f, 0.0f };
			YMath::Vector3 scale_ = { 1.0f, 1.0f, 1.0f };
		};
	public:
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="state"> : 設定用ステータス (位置、回転、大きさ)</param>
		/// <param name="state.pos_"> : 位置</param>
		/// <param name="state.rota_"> : 回転</param>
		/// <param name="state.scale_"> : 大きさ</param>
		void Initialize(const Status& state);
		// アフィン変換
		void UpdateMatrix();
		/// <summary>
		/// アフィン変換 (位置、回転、大きさ を加算したオブジェクトで行列計算)
		/// </summary>
		/// <param name="state"> : 設定用ステータス (位置、回転、大きさ)</param>
		void UpdateMatrix(const Status& state);
	protected:
		BaseObject();
	public:
		virtual ~BaseObject() = default;
	};
}
