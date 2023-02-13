#pragma once

namespace YMath
{
	struct Matrix4
	{
	public:
		float m[4][4];
	public:
		Matrix4();
		Matrix4(float m00_, float m01_, float m02_, float m03_,
			 float m10_, float m11_, float m12_, float m13_,
			 float m20_, float m21_, float m22_, float m23_,
			 float m30_, float m31_, float m32_, float m33_);
		Matrix4 operator*(const Matrix4& mat) const;
		static Matrix4 Identity();
	};

	Matrix4& operator*=(Matrix4& m1_, const Matrix4& m2);

	using Mat4 = Matrix4;
}