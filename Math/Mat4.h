#pragma once

namespace Math
{
	struct Mat4
	{
	public:
		float m[4][4];
	public:
		Mat4();
		struct InitState
		{
			float m00 = 0.0f; float m01 = 0.0f; float m02 = 0.0f; float m03 = 0.0f;
			float m10 = 0.0f; float m11 = 0.0f; float m12 = 0.0f; float m13 = 0.0f;
			float m20 = 0.0f; float m21 = 0.0f; float m22 = 0.0f; float m23 = 0.0f;
			float m30 = 0.0f; float m31 = 0.0f; float m32 = 0.0f; float m33 = 0.0f;
		};
		Mat4(const InitState& mat);
		Mat4 operator*(const Mat4& mat) const;
		static Mat4 Identity();
	};

	Mat4& operator*=(Mat4& m1, const Mat4& m2);
}