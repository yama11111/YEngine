#pragma once

namespace Math
{
	struct Vec4
	{
	public:
		float r_;
		float g_;
		float b_;
		float a_;
	public:
		// コンストラクタ(零ベクトル)
		Vec4();
		// コンストラクタ(引数有)
		Vec4(float r, float g, float b, float a);
	};
}
