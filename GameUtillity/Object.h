#pragma once
#include "ConstBuffer.h"
#include "Vec3.h"
#include "Mat4.h"

namespace YGame
{
	template<typename T>
	class Object
	{
	public:
		// 位置
		YMath::Vec3 pos_;
		// 回転
		YMath::Vec3 rota_;
		// 大きさ
		YMath::Vec3 scale_;
		// 行列
		YMath::Mat4 m_;
		// 親行列
		YMath::Mat4* parent_;
		// 定数バッファ
		YDX::ConstBuffer<T> cBuff_;
	public:
		// 設定用ステータス(位置、回転、大きさ)
		struct Status
		{
			YMath::Vec3 pos_ = { 0.0f, 0.0f, 0.0f };
			YMath::Vec3 rota_ = { 0.0f, 0.0f, 0.0f };
			YMath::Vec3 scale_ = { 1.0f, 1.0f, 1.0f };
		};
	public:
		// 初期化
		void Initialize(const Status& state);
		// アフィン変換
		void UpdateMatrix();
		// アフィン変換 (演出用)
		void UpdateMatrix(const Status& state);
	public:
		// コンストラクタ
		Object();
		// デストラクタ
		~Object() = default;
	};
}
