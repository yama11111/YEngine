#pragma once
#include "Mat4.h"

namespace Math
{
	struct MatProjection
	{
	public:
		// 転送用行列
		Mat4 m_;
	public:
		// 射影変換列挙
		enum Projection
		{
			// 平行投影変換
			OrthoGraphic = 0,
			// 透視投影変換
			Perspective = 1,
		};
		// コンストラクタ
		MatProjection(const int projection);
		// 初期化
		void Initialize(const int projection);
	};
}

