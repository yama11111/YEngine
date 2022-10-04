#include "Calc.h"
#include "DirectXMath.h"
#include "Def.h"
#include <cmath>

using Math::Vec3;
using Math::Vec4;
using Math::Mat4;

Mat4 Math::MatScale(const Vec3& s)
{
	Mat4 matScale({
	s.x, 0.0f, 0.0f, 0.0f,
	0.0f, s.y, 0.0f, 0.0f,
	0.0f, 0.0f, s.z, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
		});
	return matScale;
}

Mat4 Math::MatRotationX(float angle)
{
	Mat4 matRota({
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, (float)cos(angle), (float)sin(angle), 0.0f,
		0.0f, (float)-sin(angle), (float)cos(angle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		});
	return matRota;
}
Mat4 Math::MatRotationY(float angle)
{
	Mat4 matRota({
		(float)cos(angle), 0.0f, (float)-sin(angle), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		(float)sin(angle), 0.0f, (float)cos(angle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		});
	return matRota;
}
Mat4 Math::MatRotationZ(float angle)
{
	Mat4 matRota({
		(float)cos(angle), (float)sin(angle), 0.0f, 0.0f,
		(float)-sin(angle), (float)cos(angle), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		});
	return matRota;
}
Mat4 Math::MatRotation(const Vec3& r)
{
	Mat4 m = Mat4::Identity();
	m *= MatRotationZ(r.z) * MatRotationX(r.x) * MatRotationY(r.y);

	return m;
}

Mat4 Math::MatTranslation(const Vec3& t)
{
	Mat4 matMove({
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		t.x, t.y, t.z, 1.0f
		});
	return matMove;
}

Vec3 Math::MatTransform(const Vec3& v, const Mat4& m)
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
Vec3 Math::operator*(const Vec3& v, const Mat4& m)
{
	return MatTransform(v, m);
}

Vec3 Math::MultVec3Mat4(const Vec3& v, const Mat4& m)
{
	Vec3 result
	{
		v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0],
		v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1],
		v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2]
	};
	return result;
}

Vec4 Math::MultVec4Mat4(const Vec4& v, const Mat4& m)
{
	Vec4 result
	{
		v.r * m.m[0][0] + v.g * m.m[1][0] + v.b * m.m[2][0] + v.a * m.m[3][0],
		v.r * m.m[0][1] + v.g * m.m[1][1] + v.b * m.m[2][1] + v.a * m.m[3][1],
		v.r * m.m[0][2] + v.g * m.m[1][2] + v.b * m.m[2][2] + v.a * m.m[3][2],
		v.r * m.m[0][3] + v.g * m.m[1][3] + v.b * m.m[2][3] + v.a * m.m[3][3]
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

Mat4 Math::InverceMat4(const Mat4& m)
{
	DirectX::XMMATRIX mat = ConvertMat4(m);
	DirectX::XMMATRIX inv = DirectX::XMMatrixInverse(nullptr, mat);

	return ConvertMatrix(inv);
}

Mat4 Math::MatOrthoGraphic()
{
	DirectX::XMMATRIX mat =
		DirectX::XMMatrixOrthographicOffCenterLH(
			0.0f, WIN_SIZE.x, // 左端, 右端
			WIN_SIZE.y, 0.0f, // 下端, 上端
			0.0f, 1.0f        // 前端, 奥端
		);
	return ConvertMatrix(mat);
}
Mat4 Math::MatPerspective()
{
	DirectX::XMMATRIX mat =
		DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(45.0f), // 上下画角45度
			(float)WIN_SIZE.x / WIN_SIZE.y,		// アスペクト比 (画面横幅/画面縦幅)
			0.1f, 1000.0f						// 前端, 奥端
		);
	return ConvertMatrix(mat);
}
Mat4 Math::MatViewPort()
{
	Mat4 result = Mat4::Identity();

	result.m[0][0] = WIN_SIZE.x / 2.0f;
	result.m[3][0] = WIN_SIZE.x / 2.0f;
	result.m[1][1] = -WIN_SIZE.y / 2.0f;
	result.m[3][1] = WIN_SIZE.y / 2.0f;
	return result;
}

static DirectX::XMVECTOR ConvertXMVector(const Vec3& vec) 
{
	DirectX::XMVECTOR vector = { vec.x, vec.y, vec.z };
	return vector;
}
Mat4 Math::MatLookAtLH(const Vec3& eye, const Vec3& target, const Vec3& up)
{
	DirectX::XMMATRIX mat =
		DirectX::XMMatrixLookAtLH(
			ConvertXMVector(eye), ConvertXMVector(target), ConvertXMVector(up));

	return ConvertMatrix(mat);
}

Vec3 Math::WorldPos(const Vec2& screen, float z, const Mat4& view, const Mat4& projection)
{
	Mat4 inv = InverceMat4(view * projection * MatViewPort());
	Vec3 pos(screen.x, screen.y, z);
	Vec3 result = MatTransform(pos, inv);

	return result;
}

Vec3 Math::AdjustAngle(Vec3& velocity)
{
	Vec3 result{};
	result.y = std::atan2(velocity.x, velocity.z);
	Vec3 v = { velocity.x, 0.0f, velocity.z };
	float xz = v.Length();
	result.x = std::atan2(-velocity.y, xz);
	return result;
}

float Math::Lerp(const float a, const float b, const float t)
{
	return a + t * (b - a);
}

Vec3 Math::Lerp(const Vec3& v1, const Vec3& v2, float t)
{
	//Vec3 result = ((v2 - v1) * t) + v1;
	//return result;
	return Vec3();
}
Vec3 Math::Slerp(const Vec3& v1, const Vec3& v2, float t)
{
	//float dot = v1.Dot(v2);
	//if (dot >= 1.0 || dot <= -1.0) return v1;

	//float theta = acosf(dot);
	//float sTheta = sinf(theta);
	//float sf = sinf((1 - t) * theta);
	//float st = sinf(t * theta);

	//float aS = v1.Length();
	//float bS = v2.Length();
	//float s = aS + t * (bS - aS);

	//Vec3 from = v1 * sf;
	//Vec3 to = v2 * st / sTheta;
	//Vec3 result = (from + to) * s;
	//return result;

	return Vec3();
}

Vec4 Math::GetColor(const Vec4& color)
{
	Vec4 result = color;
	result.r /= 255.0f;
	result.g /= 255.0f;
	result.b /= 255.0f;
	result.a /= 255.0f;

	return result;
}

bool Math::CollRaySphere(	const Vec3& ray, const Vec3& velocity, 
					const Vec3& sphere, const float rad)
{
	Vec3 p = sphere - ray;

	float a = velocity.Dot(velocity);
	if (a == 0.0f) return false;
	float b = velocity.Dot(p);
	float c = p.Dot(p) - (rad * rad);

	float s = b * b - a * c;
	if (s < 0.0f) return false;

	float a1 = (b - sqrtf(s)) / a;
	float a2 = (b + sqrtf(s)) / a;
	if (a1 < 0.0f || a2 < 0.0f) return false;

	return true;
}

bool Math::CollRaySphere(	const Vec3& ray, const Vec3& velocity, 
					const Vec3& sphere, const float rad,
					Vec3& start, Vec3& end)
{
	Vec3 p = sphere - ray;

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

	end.x = ray.x + a2 * velocity.x;
	end.y = ray.y + a2 * velocity.y;
	end.z = ray.z + a2 * velocity.z;

	return true;
}
