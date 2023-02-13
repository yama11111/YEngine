#pragma once
#include "ConstBuffer.h"
#include "Vector3.h"
#include "Matrix4.h"

namespace YGame
{
	template<typename T>
	class Object
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
		// 定数バッファ
		YDX::ConstBuffer<T> cBuff_;
	public:
		// 設定用ステータス(位置、回転、大きさ)
		struct Status
		{
			YMath::Vector3 pos_ = { 0.0f, 0.0f, 0.0f };
			YMath::Vector3 rota_ = { 0.0f, 0.0f, 0.0f };
			YMath::Vector3 scale_ = { 1.0f, 1.0f, 1.0f };
		};
	public:
		// 生成
		static Object<T>* Create(const Status& state);
	public:
		// 初期化
		void Initialize(const Status& state);
		// アフィン変換
		void UpdateMatrix();
		// アフィン変換 (演出用)
		void UpdateMatrix(const Status& state);
	public:
		Object();
	public:
		~Object() = default;
	};
}
