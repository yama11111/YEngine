#include "Calc.h"
#include <cmath>

Mat4 MatScale(const Vec3& s)
{
	Mat4 matScale({
	s.x, 0.0f, 0.0f, 0.0f,
	0.0f, s.y, 0.0f, 0.0f,
	0.0f, 0.0f, s.z, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
		});
	return matScale;
}

Mat4 MatRotateX(float angle)
{
	Mat4 matRota({
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, (float)cos(angle), (float)sin(angle), 0.0f,
		0.0f, (float)-sin(angle), (float)cos(angle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		});
	return matRota;
}

Mat4 MatRotateY(float angle)
{
	Mat4 matRota({
		(float)cos(angle), 0.0f, (float)-sin(angle), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		(float)sin(angle), 0.0f, (float)cos(angle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		});
	return matRota;
}

Mat4 MatRotateZ(float angle)
{
	Mat4 matRota({
		(float)cos(angle), (float)sin(angle), 0.0f, 0.0f,
		(float)-sin(angle), (float)cos(angle), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		});
	return matRota;
}

Mat4 MatTranslate(const Vec3& t)
{
	Mat4 matMove({
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		t.x, t.y, t.z, 1.0f
		});
	return matMove;
}

Vec3 MatTransform(const Vec3& v, const Mat4& m)
{
	float w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];
	Vec3 result
	{
		(v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0]) / w,
		(v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1]) / w,
		(v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2]) / w
	};
	return result;
}

Vec3 operator*(const Vec3& v, const Mat4& m)
{
	return MatTransform(v, m);
}