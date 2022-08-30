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

Vec4 MultVec4Mat4(const Vec4& v, const Mat4& m)
{
	Vec4 result
	{
		v.r * m.m[0][0] + v.g * m.m[1][0] + v.b * m.m[2][0] + v.a * m.m[3][0],
		v.r * m.m[0][1] + v.g * m.m[1][1] + v.b * m.m[2][1] + v.a * m.m[3][1],
		v.r * m.m[0][2] + v.g * m.m[1][2] + v.b * m.m[2][2] + v.a * m.m[3][2],
		v.r * m.m[0][2] + v.g * m.m[1][2] + v.b * m.m[2][2] + v.a * m.m[3][3]
	};
	return result;
}

static Mat4 ConvertMatrix(const DirectX::XMMATRIX mat)
{
	Mat4 r = Mat4(
		{
			mat.r[0].m128_f32[0], mat.r[0].m128_f32[1], mat.r[0].m128_f32[2], mat.r[0].m128_f32[3],
			mat.r[1].m128_f32[0], mat.r[1].m128_f32[1], mat.r[1].m128_f32[2], mat.r[1].m128_f32[3],
			mat.r[2].m128_f32[0], mat.r[2].m128_f32[1], mat.r[2].m128_f32[2], mat.r[2].m128_f32[3],
			mat.r[3].m128_f32[0], mat.r[3].m128_f32[1], mat.r[3].m128_f32[2], mat.r[3].m128_f32[3]
		}
	);
	return r;
}

static DirectX::XMMATRIX ConvertMat4(const Mat4& mat)
{
	DirectX::XMMATRIX r = DirectX::XMMATRIX(
		mat.m[0][0], mat.m[0][1], mat.m[0][2], mat.m[0][3],
		mat.m[1][0], mat.m[1][1], mat.m[1][2], mat.m[1][3],
		mat.m[2][0], mat.m[2][1], mat.m[2][2], mat.m[2][3],
		mat.m[3][0], mat.m[3][1], mat.m[3][2], mat.m[3][3]
	);
	return r;
}

Mat4 InverceMat4(const Mat4& m)
{
	DirectX::XMMATRIX mat = ConvertMat4(m);
	DirectX::XMMATRIX inv = DirectX::XMMatrixInverse(nullptr, mat);

	return ConvertMatrix(inv);
}

Mat4 MatOrthoGraphic()
{
	DirectX::XMMATRIX mat =
		DirectX::XMMatrixOrthographicOffCenterLH(
			0.0f, WIN_SIZE.x, // 左端, 右端
			WIN_SIZE.y, 0.0f, // 下端, 上端
			0.0f, 1.0f        // 前端, 奥端
		);
	return ConvertMatrix(mat);
}
Mat4 MatPerspective()
{
	DirectX::XMMATRIX mat =
		DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(45.0f), // 上下画角45度
			(float)WIN_SIZE.x / WIN_SIZE.y,		// アスペクト比 (画面横幅/画面縦幅)
			0.1f, 1000.0f						// 前端, 奥端
		);
	return ConvertMatrix(mat);
}
Mat4 MatViewPort()
{
	Mat4 result = Mat4::Identity();
	result.m[0][0] = WIN_SIZE.x / 2.0f;
	result.m[3][0] = -WIN_SIZE.x / 2.0f;
	result.m[1][1] = WIN_SIZE.y / 2.0f;
	result.m[3][1] = WIN_SIZE.y / 2.0f;
	result.m[2][2] = 1000.0f - 0.1f;
	result.m[3][2] = 0.1f;
	return result;
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

Vec3 WorldPos(const Vec2& screen, float z, const MatViewProjection& vp)
{
	Mat4 iView = InverceMat4(vp.view.m);
	Mat4 iPro = InverceMat4(vp.pro.m);
	Mat4 iVP = InverceMat4(MatViewPort());
	Mat4 inv = iVP * iPro * iView;
	Vec4 pos(screen.x - WIN_SIZE.x / 2.0f, screen.y - WIN_SIZE.y / 2.0f, z, 1.0f);
	Vec4 r = MultVec4Mat4(pos, inv);
	Vec3 result(pos.r, -pos.g, pos.b);
	result /= r.a;

	return result;
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

Vec4 GetColor(const Vec4& color)
{
	Vec4 result = color;
	result.r /= 255.0f;
	result.g /= 255.0f;
	result.b /= 255.0f;
	result.a /= 255.0f;

	return result;
}

bool CollRaySphere(	const Vec3& ray, const Vec3& velocity, 
					const Vec3& sphere, const float rad, Vec3& start)
{
	Vec3 p = sphere;
	p -= ray;

	float a = velocity.Dot(velocity);
	if (a == 0.0f) return false;
	float b = velocity.Dot(p);
	float c = p.Dot(p) - (rad * rad);

	float s = b * b - a * c;
	if (s < 0.0f) return false;

	float a1 = (b - sqrtf(s)) / a;
	float a2 = (b + sqrtf(s)) / a;

	if (a1 < 0.0f || a2 < 0.0f) return false;

	start.x = ray.x + a1 * velocity.x;
	start.y = ray.y + a1 * velocity.y;
	start.z = ray.z + a1 * velocity.z;

	return true;
}
