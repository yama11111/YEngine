#include "CalcTransform.h"
#include "DirectXMath.h"
#include "Def.h"
#include <cmath>

using YMath::Vec3;
using YMath::Vec4;
using YMath::Mat4;

#pragma region DirectXMath系

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

static DirectX::XMVECTOR ConvertXMVector(const Vec3& vec)
{
	DirectX::XMVECTOR vector = { vec.x_, vec.y_, vec.z_ };
	return vector;
}

#pragma endregion

#pragma region 変換系

// ------------ アフィン変換 ------------ //

Mat4 YMath::MatScale(const Vec3& s)
{
	Mat4 matScale({
	s.x_, 0.0f, 0.0f, 0.0f,
	0.0f, s.y_, 0.0f, 0.0f,
	0.0f, 0.0f, s.z_, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
		});
	return matScale;
}

Mat4 YMath::MatRotationX(float angle)
{
	Mat4 matRota({
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, (float)cos(angle), (float)sin(angle), 0.0f,
		0.0f, (float)-sin(angle), (float)cos(angle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		});
	return matRota;
}
Mat4 YMath::MatRotationY(float angle)
{
	Mat4 matRota({
		(float)cos(angle), 0.0f, (float)-sin(angle), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		(float)sin(angle), 0.0f, (float)cos(angle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		});
	return matRota;
}
Mat4 YMath::MatRotationZ(float angle)
{
	Mat4 matRota({
		(float)cos(angle), (float)sin(angle), 0.0f, 0.0f,
		(float)-sin(angle), (float)cos(angle), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		});
	return matRota;
}
Mat4 YMath::MatRotation(const Vec3& r)
{
	Mat4 m = MatRotationZ(r.z_) * MatRotationX(r.x_) * MatRotationY(r.y_);
	return m;
}

Mat4 YMath::MatTranslation(const Vec3& t)
{
	Mat4 matMove({
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		t.x_, t.y_, t.z_, 1.0f
		});
	return matMove;
}

// ----- ビュープロジェクション変換 ----- //

Mat4 YMath::MatOrthoGraphic()
{
	DirectX::XMMATRIX mat =
		DirectX::XMMatrixOrthographicOffCenterLH(
			0.0f, WinSize.x_, // 左端, 右端
			WinSize.y_, 0.0f, // 下端, 上端
			0.0f, 1.0f        // 前端, 奥端
		);
	return ConvertMatrix(mat);
}
Mat4 YMath::MatPerspective()
{
	DirectX::XMMATRIX mat =
		DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(45.0f), // 上下画角45度
			(float)WinSize.x_ / WinSize.y_,		// アスペクト比 (画面横幅/画面縦幅)
			0.1f, 1000.0f						// 前端, 奥端
		);
	return ConvertMatrix(mat);
}
Mat4 YMath::MatViewPort()
{
	Mat4 result = Mat4::Identity();

	result.m[0][0] = +WinSize.x_ / 2.0f;
	result.m[3][0] = +WinSize.x_ / 2.0f;
	result.m[1][1] = -WinSize.y_ / 2.0f;
	result.m[3][1] = +WinSize.y_ / 2.0f;
	return result;
}
Mat4 YMath::MatLookAtLH(const Vec3& eye, const Vec3& target, const Vec3& up)
{
	DirectX::XMMATRIX mat =
		DirectX::XMMatrixLookAtLH(
			ConvertXMVector(eye), ConvertXMVector(target), ConvertXMVector(up));

	return ConvertMatrix(mat);
}

#pragma endregion

Vec3 YMath::MatTransform(const Vec3& v, const Mat4& m)
{
	float w = v.x_ * m.m[0][3] + v.y_ * m.m[1][3] + v.z_ * m.m[2][3] + m.m[3][3];
	Vec3 result
	{
		(v.x_ * m.m[0][0] + v.y_ * m.m[1][0] + v.z_ * m.m[2][0] + m.m[3][0]) / w,
		(v.x_ * m.m[0][1] + v.y_ * m.m[1][1] + v.z_ * m.m[2][1] + m.m[3][1]) / w,
		(v.x_ * m.m[0][2] + v.y_ * m.m[1][2] + v.z_ * m.m[2][2] + m.m[3][2]) / w
	};
	return result;
}
Vec3 YMath::operator*(const Vec3& v, const Mat4& m)
{
	return MatTransform(v, m);
}

Vec3 YMath::MultVec3Mat4(const Vec3& v, const Mat4& m)
{
	Vec3 result
	{
		v.x_ * m.m[0][0] + v.y_ * m.m[1][0] + v.z_ * m.m[2][0],
		v.x_ * m.m[0][1] + v.y_ * m.m[1][1] + v.z_ * m.m[2][1],
		v.x_ * m.m[0][2] + v.y_ * m.m[1][2] + v.z_ * m.m[2][2]
	};
	return result;
}

Vec4 YMath::MultVec4Mat4(const Vec4& v, const Mat4& m)
{
	Vec4 result
	{
		v.r_ * m.m[0][0] + v.g_ * m.m[1][0] + v.b_ * m.m[2][0] + v.a_ * m.m[3][0],
		v.r_ * m.m[0][1] + v.g_ * m.m[1][1] + v.b_ * m.m[2][1] + v.a_ * m.m[3][1],
		v.r_ * m.m[0][2] + v.g_ * m.m[1][2] + v.b_ * m.m[2][2] + v.a_ * m.m[3][2],
		v.r_ * m.m[0][3] + v.g_ * m.m[1][3] + v.b_ * m.m[2][3] + v.a_ * m.m[3][3]
	};
	return result;
}

Mat4 YMath::InverceMat4(const Mat4& m)
{
	DirectX::XMMATRIX mat = ConvertMat4(m);
	DirectX::XMMATRIX inv = DirectX::XMMatrixInverse(nullptr, mat);

	return ConvertMatrix(inv);
}

Vec3 YMath::WorldPos(const Vec2& screen, float z, const Mat4& view, const Mat4& projection)
{
	Mat4 inv = InverceMat4(view * projection * MatViewPort());
	Vec3 pos(screen.x_, screen.y_, z);
	Vec3 result = MatTransform(pos, inv);

	return result;
}

Vec3 YMath::AdjustAngle(const Vec3& velocity)
{
	Vec3 result{};
	result.y_ = std::atan2(velocity.x_, velocity.z_);
	Vec3 v = { velocity.x_, 0.0f, velocity.z_ };
	float xz = v.Length();
	result.x_ = std::atan2(-velocity.y_, xz);
	return result;
}
