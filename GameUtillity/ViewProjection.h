#pragma once
#include "Vec3.h"
#include "Mat4.h"

namespace YGame
{
	class ViewProjection
	{
	public:
		// 視点
		YMath::Vec3 eye_;
		// 注視点
		YMath::Vec3 target_;
		// 上方向ベクトル
		YMath::Vec3 up_;
		// ビュー行列
		YMath::Mat4 view_;
		// プロジェクション行列
		YMath::Mat4 pro_;
	public:
		// 初期化用ステータス(視点、注視点、上方向ベクトル)
		struct InitStatus
		{
			YMath::Vec3 eye_ = { 0.0f, 0.0f, -100.0f };
			YMath::Vec3 target_ = { 0.0f, 0.0f, 0.0f };
			YMath::Vec3 up_ = { 0.0f, 1.0f, 0.0f };
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