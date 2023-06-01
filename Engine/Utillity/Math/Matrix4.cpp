#include "Matrix4.h"

using YMath::Matrix4;

Matrix4::Matrix4()
{
	m_[0][0] = 0.0f, m_[0][1] = 0.0f, m_[0][2] = 0.0f, m_[0][3] = 0.0f;
	m_[1][0] = 0.0f, m_[1][1] = 0.0f, m_[1][2] = 0.0f, m_[1][3] = 0.0f;
	m_[2][0] = 0.0f, m_[2][1] = 0.0f, m_[2][2] = 0.0f, m_[2][3] = 0.0f;
	m_[3][0] = 0.0f, m_[3][1] = 0.0f, m_[3][2] = 0.0f, m_[3][3] = 0.0f;
}

Matrix4::Matrix4( float m00_, float m01_, float m02_, float m03_,
			float m10_, float m11_, float m12_, float m13_,
			float m20_, float m21_, float m22_, float m23_,
			float m30_, float m31_, float m32_, float m33_) :
	m_()
{
	m_[0][0] = m00_, m_[0][1] = m01_, m_[0][2] = m02_, m_[0][3] = m03_;
	m_[1][0] = m10_, m_[1][1] = m11_, m_[1][2] = m12_, m_[1][3] = m13_;
	m_[2][0] = m20_, m_[2][1] = m21_, m_[2][2] = m22_, m_[2][3] = m23_;
	m_[3][0] = m30_, m_[3][1] = m31_, m_[3][2] = m32_, m_[3][3] = m33_;
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
				m2.m_[i][j] += m_[i][k] * mat.m_[k][j];
			}
		}
	}

	return m2;
}

Matrix4 Matrix4::Identity()
{
	const static Matrix4 m_
	({
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		});

	return m_;
}

Matrix4& YMath::operator*=(Matrix4& m1_, const Matrix4& m2)
{
	Matrix4 m_ = Matrix4();
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			for (int k = 0; k < 4; k++) 
			{
				m_.m_[i][j] += m1_.m_[i][k] * m2.m_[k][j];
			}
		}
	}

	m1_ = m_;
	return m1_;
}