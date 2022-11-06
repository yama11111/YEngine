#pragma once
#include "Vec3.h"
#include "Mat4.h"

namespace Math
{
	struct MatWorld
	{
	public:
		// 転送用行列
		Mat4 m_;
		// 位置
		Vec3 pos_;
		// 角度
		Vec3 rota_;
		// 大きさ
		Vec3 scale_;
	public:
		// 初期化用ステータス
		struct InitStatus
		{
			Vec3 pos_ = { 0.0f, 0.0f, 0.0f };
			Vec3 rota_ = { 0.0f, 0.0f, 0.0f };
			Vec3 scale_ = { 1.0f, 1.0f, 1.0f };
		};
	public:
		// コンストラクタ
		MatWorld();
		// コンストラクタ (引数有)
		MatWorld(const InitStatus& init);
		// 初期化
		void Initialize(const InitStatus& init);
		// アフィン変換 → 転送用行列に代入
		void Update();
	};
}
