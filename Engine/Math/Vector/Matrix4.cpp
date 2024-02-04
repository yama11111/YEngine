#include "Matrix4.h"

using YMath::Matrix4;

Matrix4::Matrix4()
{
	m[0][0] = 0.0f, m[0][1] = 0.0f, m[0][2] = 0.0f, m[0][3] = 0.0f;
	m[1][0] = 0.0f, m[1][1] = 0.0f, m[1][2] = 0.0f, m[1][3] = 0.0f;
	m[2][0] = 0.0f, m[2][1] = 0.0f, m[2][2] = 0.0f, m[2][3] = 0.0f;
	m[3][0] = 0.0f, m[3][1] = 0.0f, m[3][2] = 0.0f, m[3][3] = 0.0f;
}

Matrix4::Matrix4( 
	float m00, float m01, float m02, float m03,
	float m10, float m11, float m12, float m13,
	float m20, float m21, float m22, float m23,
	float m30, float m31, float m32, float m33) :
	m()
{
	m[0][0] = m00, m[0][1] = m01, m[0][2] = m02, m[0][3] = m03;
	m[1][0] = m10, m[1][1] = m11, m[1][2] = m12, m[1][3] = m13;
	m[2][0] = m20, m[2][1] = m21, m[2][2] = m22, m[2][3] = m23;
	m[3][0] = m30, m[3][1] = m31, m[3][2] = m32, m[3][3] = m33;
}

Matrix4 Matrix4::operator*(const Matrix4& mat) const
{
	Matrix4 m2 = Matrix4();
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

Matrix4 Matrix4::Identity()
{
	const static Matrix4 m
	({
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		});

	return m;
}

Matrix4& YMath::operator*=(Matrix4& m1, const Matrix4& m2)
{
	Matrix4 m = Matrix4();
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