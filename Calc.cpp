#include "Calc.h"
#include "DirectXMath.h"
#include "Def.h"
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

Mat4 MatRotationX(float angle)
{
	Mat4 matRota({
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, (float)cos(angle), (float)sin(angle), 0.0f,
		0.0f, (float)-sin(angle), (float)cos(angle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		});
	return matRota;
}
Mat4 MatRotationY(float angle)
{
	Mat4 matRota({
		(float)cos(angle), 0.0f, (float)-sin(angle), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		(float)sin(angle), 0.0f, (float)cos(angle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		});
	return matRota;
}
Mat4 MatRotationZ(float angle)
{
	Mat4 matRota({
		(float)cos(angle), (float)sin(angle), 0.0f, 0.0f,
		(float)-sin(angle), (float)cos(angle), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		});
	return matRota;
}
Mat4 MatRotation(const Vec3& r)
{
	Mat4 m = Mat4::Identity();
	m *= MatRotationZ(r.z) * MatRotationX(r.x) * MatRotationY(r.y);

	return m;
}

Mat4 MatTranslation(const Vec3& t)
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

Vec3 MultVec3Mat4(const Vec3& v, const Mat4& m)
{
	Vec3 result
	{
		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]
	};
	return result;
}

static Mat4 ConvertMatrix(const DirectX::XMMATRIX mat)
{
	Mat4 r;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++) 
		{
			r.m[i][j] = mat.r[i].m128_f32[j];
		}
	}
	return r;
}
Mat4 MatOrthoGraphic()
{
	DirectX::XMMATRIX mat =
		DirectX::XMMatrixOrthographicOffCenterLH(
			0.0f, WIN_SIZE.x, // ���[, �E�[
			WIN_SIZE.y, 0.0f, // ���[, ��[
			0.0f, 1.0f        // �O�[, ���[
		);
	return ConvertMatrix(mat);
}
Mat4 MatPerspective()
{
	DirectX::XMMATRIX mat =
		DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(45.0f), // �㉺��p45�x
			(float)WIN_SIZE.x / WIN_SIZE.y,		// �A�X�y�N�g�� (��ʉ���/��ʏc��)
			0.1f, 1000.0f						// �O�[, ���[
		);
	return ConvertMatrix(mat);
}

static DirectX::XMVECTOR ConvertXMVector(const Vec3& vec) 
{
	DirectX::XMVECTOR vector = { vec.x, vec.y, vec.z };
	return vector;
}
Mat4 MatLookAtLH(const Vec3& eye, const Vec3& target, const Vec3& up)
{
	DirectX::XMMATRIX mat =
		DirectX::XMMatrixLookAtLH(
			ConvertXMVector(eye), ConvertXMVector(target), ConvertXMVector(up));

	return ConvertMatrix(mat);
}

Vec3 AdjustAngle(Vec3& velocity)
{
	Vec3 result{};
	result.y = std::atan2(velocity.x, velocity.z);
	Vec3 v = { velocity.x, 0.0f, velocity.z };
	float xz = v.Length();
	result.x = std::atan2(-velocity.y, xz);
	return result;
}

Vec3 Lerp(const Vec3& v1, const Vec3& v2, float t)
{
	Vec3 result = v2 - v1;
	result *= t;
	result += v1;
	return result;
}
Vec3 Slerp(const Vec3& v1, const Vec3& v2, float t)
{
	float dot = v1.Dot(v2);
	if (dot >= 1.0 || dot <= -1.0) return v1;

	float theta = acosf(dot);
	float sTheta = sinf(theta);
	float sf = sinf((1 - t) * theta);
	float st = sinf(t * theta);

	float aS = v1.Length();
	float bS = v2.Length();
	float s = aS + t * (bS - aS);

	Vec3 from = v1;
	from *= sf;
	Vec3 to = v2;
	to *= st;
	to /= sTheta;
	Vec3 e = from;
	e += to;
	e *= s;
	return e;
}
