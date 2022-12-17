#pragma once

namespace Math
{
	struct Mat4
	{
	public:
		float m[4][4];
	public:
		Mat4();
		Mat4(float m00_, float m01_, float m02_, float m03_,
			 float m10_, float m11_, float m12_, float m13_,
			 float m20_, float m21_, float m22_, float m23_,
			 float m30_, float m31_, float m32_, float m33_);
		Mat4 operator*(const Mat4& mat) const;
		static Mat4 Identity();
	};

	Mat4& operator*=(Mat4& m1_, const Mat4& m2);
}