#pragma once
#include "Vector3.h"
#include "Matrix4.h"

namespace YGame
{
	class ViewProjection
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
		// 初期化用ステータス(視点、注視点、上方向ベクトル)
		struct InitStatus
		{
			YMath::Vector3 eye_ = { 0.0f, 0.0f, -100.0f };
			YMath::Vector3 target_ = { 0.0f, 0.0f, 0.0f };
			YMath::Vector3 up_ = { 0.0f, 1.0f, 0.0f };
		};
	public:
		// コンストラクタ
		ViewProjection();
		// 初期化
		void Initialize(const InitStatus& state);
		// ビュー変換 + プロジェクション変換
		void Update();
	};
}