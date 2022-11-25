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
			float m00_ = 0.0f; float m01_ = 0.0f; float m02_ = 0.0f; float m03_ = 0.0f;
			float m10_ = 0.0f; float m11_ = 0.0f; float m12_ = 0.0f; float m13_ = 0.0f;
			float m20_ = 0.0f; float m21_ = 0.0f; float m22_ = 0.0f; float m23_ = 0.0f;
			float m30_ = 0.0f; float m31_ = 0.0f; float m32_ = 0.0f; float m33_ = 0.0f;
		};
		Mat4(const InitState& mat);
		Mat4 operator*(const Mat4& mat) const;
		static Mat4 Identity();
	};

	Mat4& operator*=(Mat4& m1_, const Mat4& m2);
}