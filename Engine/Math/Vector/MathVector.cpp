#include "MathVector.h"
#include "DirectXMath.h"
#include "Def.h"
#include <cmath>

using YMath::Vector3;
using YMath::Vector4;
using YMath::Matrix4;

#pragma region DirectXMath系

static Matrix4 ConvertMatrix(const DirectX::XMMATRIX mat)
{
	Matrix4 r = Matrix4(
		{
			mat.r[0].m128_f32[0], mat.r[0].m128_f32[1], mat.r[0].m128_f32[2], mat.r[0].m128_f32[3],
			mat.r[1].m128_f32[0], mat.r[1].m128_f32[1], mat.r[1].m128_f32[2], mat.r[1].m128_f32[3],
			mat.r[2].m128_f32[0], mat.r[2].m128_f32[1], mat.r[2].m128_f32[2], mat.r[2].m128_f32[3],
			mat.r[3].m128_f32[0], mat.r[3].m128_f32[1], mat.r[3].m128_f32[2], mat.r[3].m128_f32[3]
		}
	);
	return r;
}

static DirectX::XMMATRIX ConvertMat4(const Matrix4& mat)
{
	DirectX::XMMATRIX r = DirectX::XMMATRIX(
		mat.m_[0][0], mat.m_[0][1], mat.m_[0][2], mat.m_[0][3],
		mat.m_[1][0], mat.m_[1][1], mat.m_[1][2], mat.m_[1][3],
		mat.m_[2][0], mat.m_[2][1], mat.m_[2][2], mat.m_[2][3],
		mat.m_[3][0], mat.m_[3][1], mat.m_[3][2], mat.m_[3][3]
	);
	return r;
}

static DirectX::XMVECTOR ConvertXMVector(const Vector3& vec)
{
	DirectX::XMVECTOR vector = { vec.x_, vec.y_, vec.z_ };
	return vector;
}

#pragma endregion

#pragma region 変換系

// ------------ アフィン変換 ------------ //

Matrix4 YMath::MatScale(const Vector3& s)
{
	Matrix4 matScale({
	s.x_, 0.0f, 0.0f, 0.0f,
	0.0f, s.y_, 0.0f, 0.0f,
	0.0f, 0.0f, s.z_, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
		});
	return matScale;
}

Matrix4 YMath::MatRotationX(float angle)
{
	Matrix4 matRota({
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, (float)cos(angle), (float)sin(angle), 0.0f,
		0.0f, (float)-sin(angle), (float)cos(angle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		});
	return matRota;
}
Matrix4 YMath::MatRotationY(float angle)
{
	Matrix4 matRota({
		(float)cos(angle), 0.0f, (float)-sin(angle), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		(float)sin(angle), 0.0f, (float)cos(angle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		});
	return matRota;
}
Matrix4 YMath::MatRotationZ(float angle)
{
	Matrix4 matRota({
		(float)cos(angle), (float)sin(angle), 0.0f, 0.0f,
		(float)-sin(angle), (float)cos(angle), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		});
	return matRota;
}
Matrix4 YMath::MatRotation(const Vector3& r)
{
	Matrix4 m = MatRotationZ(r.z_) * MatRotationX(r.x_) * MatRotationY(r.y_);
	return m;
}

Matrix4 YMath::MatTranslation(const Vector3& t)
{
	Matrix4 matMove({
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		t.x_, t.y_, t.z_, 1.0f
		});
	return matMove;
}

// ----- ビュープロジェクション変換 ----- //

Matrix4 YMath::MatOrthoGraphic()
{
	DirectX::XMMATRIX mat =
		DirectX::XMMatrixOrthographicOffCenterLH(
			0.0f, WinSize.x_, // 左端, 右端
			WinSize.y_, 0.0f, // 下端, 上端
			0.0f, 1.0f        // 前端, 奥端
		);
	return ConvertMatrix(mat);
}
Matrix4 YMath::MatPerspective()
{
	DirectX::XMMATRIX mat =
		DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(45.0f), // 上下画角45度
			(float)WinSize.x_ / WinSize.y_,		// アスペクト比 (画面横幅/画面縦幅)
			0.1f, 1000.0f						// 前端, 奥端
		);
	return ConvertMatrix(mat);
}
Matrix4 YMath::MatViewPort()
{
	Matrix4 result = Matrix4::Identity();

	result.m_[0][0] = +WinSize.x_ / 2.0f;
	result.m_[3][0] = +WinSize.x_ / 2.0f;
	result.m_[1][1] = -WinSize.y_ / 2.0f;
	result.m_[3][1] = +WinSize.y_ / 2.0f;
	return result;
}
Matrix4 YMath::MatLookAtLH(const Vector3& eye, const Vector3& target, const Vector3& up)
{
	DirectX::XMMATRIX mat =
		DirectX::XMMatrixLookAtLH(
			ConvertXMVector(eye), ConvertXMVector(target), ConvertXMVector(up));

	return ConvertMatrix(mat);
}

#pragma endregion

Vector3 YMath::MatTransform(const Vector3& v, const Matrix4& m)
{
	float w = v.x_ * m.m_[0][3] + v.y_ * m.m_[1][3] + v.z_ * m.m_[2][3] + m.m_[3][3];
	Vector3 result
	{
		(v.x_ * m.m_[0][0] + v.y_ * m.m_[1][0] + v.z_ * m.m_[2][0] + m.m_[3][0]) / w,
		(v.x_ * m.m_[0][1] + v.y_ * m.m_[1][1] + v.z_ * m.m_[2][1] + m.m_[3][1]) / w,
		(v.x_ * m.m_[0][2] + v.y_ * m.m_[1][2] + v.z_ * m.m_[2][2] + m.m_[3][2]) / w
	};
	return result;
}
Vector3 YMath::operator*(const Vector3& v, const Matrix4& m)
{
	return MatTransform(v, m);
}

Vector3 YMath::MultVec3Mat4(const Vector3& v, const Matrix4& m)
{
	Vector3 result
	{
		v.x_ * m.m_[0][0] + v.y_ * m.m_[1][0] + v.z_ * m.m_[2][0],
		v.x_ * m.m_[0][1] + v.y_ * m.m_[1][1] + v.z_ * m.m_[2][1],
		v.x_ * m.m_[0][2] + v.y_ * m.m_[1][2] + v.z_ * m.m_[2][2]
	};
	return result;
}

Vector4 YMath::MultVec4Mat4(const Vector4& v, const Matrix4& m)
{
	Vector4 result
	{
		v.r_ * m.m_[0][0] + v.g_ * m.m_[1][0] + v.b_ * m.m_[2][0] + v.a_ * m.m_[3][0],
		v.r_ * m.m_[0][1] + v.g_ * m.m_[1][1] + v.b_ * m.m_[2][1] + v.a_ * m.m_[3][1],
		v.r_ * m.m_[0][2] + v.g_ * m.m_[1][2] + v.b_ * m.m_[2][2] + v.a_ * m.m_[3][2],
		v.r_ * m.m_[0][3] + v.g_ * m.m_[1][3] + v.b_ * m.m_[2][3] + v.a_ * m.m_[3][3]
	};
	return result;
}

Matrix4 YMath::InverceMat4(const Matrix4& m)
{
	DirectX::XMMATRIX mat = ConvertMat4(m);
	DirectX::XMMATRIX inv = DirectX::XMMatrixInverse(nullptr, mat);

	return ConvertMatrix(inv);
}

Vector3 YMath::WorldPos(const Vector2& screen, float z, const Matrix4& view, const Matrix4& projection)
{
	Matrix4 inv = InverceMat4(view * projection * MatViewPort());
	Vector3 pos(screen.x_, screen.y_, z);
	Vector3 result = MatTransform(pos, inv);

	return result;
}

Vector3 YMath::AdjustAngle(const Vector3& v)
{
	Vector3 result{};
	result.y_ = std::atan2(v.x_, v.z_);
	Vector3 vec = { v.x_, 0.0f, v.z_ };
	float xz = vec.Length();
	result.x_ = std::atan2(-v.y_, xz);
	return result;
}

Matrix4 YMath::MatBillboard(const bool isXAxisBillboard, const bool isYAxisBillboard, 
	const Vector3& eye, const Vector3& target, const Vector3& up)
{
	// どちらも false なら
	if (isXAxisBillboard == false && isYAxisBillboard == false)
	{
		// 単位行列を返す
		return Matrix4::Identity();
	}

	// ビルボード行列の計算
	Vector3 axisZ = (target - eye).Normalized();
	Vector3 axisX = (up.Cross(axisZ)).Normalized();
	Vector3 axisY = axisZ.Cross(axisX);

	// Y軸周りビルボードなら
	if (isYAxisBillboard)
	{
		axisY = { 0,1,0 };
		axisZ = axisX.Cross(axisY);
	}

	// ビルボード行列
	Matrix4 matBillboard(
		axisX.x_, axisX.y_, axisX.z_, 0.0f,
		axisY.x_, axisY.y_, axisY.z_, 0.0f,
		axisZ.x_, axisZ.y_, axisZ.z_, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	// ビルボード行列を返す
	return matBillboard;
}

Vector3 YMath::ConvertToVector3(const Vector2& v)
{
	return Vector3(v.x_, v.y_, 0.0f);
}

Vector3 YMath::MultAtComponent(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x_ * v2.x_, v1.y_ * v2.y_, v1.z_ * v2.z_);
}

Vector3 YMath::DivAtComponent(const Vector3& v1, const Vector3& v2)
{
	return Vector3(v1.x_ / v2.x_, v1.y_ / v2.y_, v1.z_ / v2.z_);
}
