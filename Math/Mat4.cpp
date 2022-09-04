#include "Mat4.h"

using Math::Mat4;

Mat4::Mat4()
{
	m[0][0] = 0.0f, m[0][1] = 0.0f, m[0][2] = 0.0f, m[0][3] = 0.0f;
	m[1][0] = 0.0f, m[1][1] = 0.0f, m[1][2] = 0.0f, m[1][3] = 0.0f;
	m[2][0] = 0.0f, m[2][1] = 0.0f, m[2][2] = 0.0f, m[2][3] = 0.0f;
	m[3][0] = 0.0f, m[3][1] = 0.0f, m[3][2] = 0.0f, m[3][3] = 0.0f;
}

Mat4::Mat4(const InitState& mat) :
	m()
{
	m[0][0] = mat.m00, m[0][1] = mat.m01, m[0][2] = mat.m02, m[0][3] = mat.m03;
	m[1][0] = mat.m10, m[1][1] = mat.m11, m[1][2] = mat.m12, m[1][3] = mat.m13;
	m[2][0] = mat.m20, m[2][1] = mat.m21, m[2][2] = mat.m22, m[2][3] = mat.m23;
	m[3][0] = mat.m30, m[3][1] = mat.m31, m[3][2] = mat.m32, m[3][3] = mat.m33;
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

Mat4& Math::operator*=(Mat4& m1, const Mat4& m2)
{
	Mat4 m = Mat4();
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			for (int k = 0; k < 4; k++) 
			{
				m.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	m1 = m;
	return m1;
}