#include "Mat4.h"

using Math::Mat4;

Mat4::Mat4()
{
	m[0][0] = 0.0f, m[0][1] = 0.0f, m[0][2] = 0.0f, m[0][3] = 0.0f;
	m[1][0] = 0.0f, m[1][1] = 0.0f, m[1][2] = 0.0f, m[1][3] = 0.0f;
	m[2][0] = 0.0f, m[2][1] = 0.0f, m[2][2] = 0.0f, m[2][3] = 0.0f;
	m[3][0] = 0.0f, m[3][1] = 0.0f, m[3][2] = 0.0f, m[3][3] = 0.0f;
}

Mat4::Mat4( float m00_, float m01_, float m02_, float m03_,
			float m10_, float m11_, float m12_, float m13_,
			float m20_, float m21_, float m22_, float m23_,
			float m30_, float m31_, float m32_, float m33_) :
	m()
{
	m[0][0] = m00_, m[0][1] = m01_, m[0][2] = m02_, m[0][3] = m03_;
	m[1][0] = m10_, m[1][1] = m11_, m[1][2] = m12_, m[1][3] = m13_;
	m[2][0] = m20_, m[2][1] = m21_, m[2][2] = m22_, m[2][3] = m23_;
	m[3][0] = m30_, m[3][1] = m31_, m[3][2] = m32_, m[3][3] = m33_;
}

Mat4 Mat4::operator*(const Mat4& mat) const
{
	Mat4 m2 = Mat4();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				m2.m[i][j] += m[i][k] * mat.m[k][j];
			}
		}
	}

	return m2;
}

Mat4 Mat4::Identity()
{
	const static Mat4 m
	({
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		});

	return m;
}

Mat4& Math::operator*=(Mat4& m1_, const Mat4& m2)
{
	Mat4 m = Mat4();
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			for (int k = 0; k < 4; k++) 
			{
				m.m[i][j] += m1_.m[i][k] * m2.m[k][j];
			}
		}
	}

	m1_ = m;
	return m1_;
}