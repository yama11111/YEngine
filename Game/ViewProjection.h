#pragma once
#include "Vec3.h"
#include "Mat4.h"

namespace Game
{
	class ViewProjection
	{
	public:
		// 視点
		Math::Vec3 eye_;
		// 注視点
		Math::Vec3 target_;
		// 上方向ベクトル
		Math::Vec3 up_;
		// ビュー行列
		Math::Mat4 view_;
		// プロジェクション行列
		Math::Mat4 pro_;
	public:
		// 初期化用ステータス(視点、注視点、上方向ベクトル)
		struct InitStatus
		{
			Math::Vec3 eye_ = { 0.0f, 0.0f, -100.0f };
			Math::Vec3 target_ = { 0.0f, 0.0f, 0.0f };
			Math::Vec3 up_ = { 0.0f, 1.0f, 0.0f };
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