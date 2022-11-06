#pragma once
#include "Vec3.h"
#include "Mat4.h"

namespace Math
{
	struct MatView
	{
	public:
		// 転送用行列
		Mat4 m_;
		// 視点
		Vec3 eye_;
		// 注視点
		Vec3 target_;
		// 上方向ベクトル
		Vec3 up_;
	public:
		// 初期化用ステータス
		struct InitStatus
		{
			Vec3 eye_ = { 0.0f, 0.0f, -100.0f };
			Vec3 target_ = { 0.0f, 0.0f, 0.0f };
			Vec3 up_ = { 0.0f, 1.0f, 0.0f };
		};
	public:
		// コンストラクタ
		MatView();
		// コンストラクタ (引数有)
		MatView(const InitStatus& init);
		// 初期化
		void Initialize(const InitStatus& init);
		// ビュー変換 → 転送用行列に代入
		void Update();
	};
}
