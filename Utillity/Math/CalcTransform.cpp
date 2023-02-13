#include "CalcTransform.h"
#include "DirectXMath.h"
#include "Def.h"
#include <cmath>

using YMath::Vector3;
using YMath::Vector4;
using YMath::Matrix4;

#pragma region DirectXMath�n

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
		mat.m[0][0], mat.m[0][1], mat.m[0][2], mat.m[0][3],
		mat.m[1][0], mat.m[1][1], mat.m[1][2], mat.m[1][3],
		mat.m[2][0], mat.m[2][1], mat.m[2][2], mat.m[2][3],
		mat.m[3][0], mat.m[3][1], mat.m[3][2], mat.m[3][3]
	);
	return r;
}

static DirectX::XMVECTOR ConvertXMVector(const Vector3& vec)
{
	DirectX::XMVECTOR vector = { vec.x_, vec.y_, vec.z_ };
	return vector;
}

#pragma endregion

#pragma region �ϊ��n

// ------------ �A�t�B���ϊ� ------------ //

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

// ----- �r���[�v���W�F�N�V�����ϊ� ----- //

Matrix4 YMath::MatOrthoGraphic()
{
	DirectX::XMMATRIX mat =
		DirectX::XMMatrixOrthographicOffCenterLH(
			0.0f, WinSize.x_, // ���[, �E�[
			WinSize.y_, 0.0f, // ���[, ��[
			0.0f, 1.0f        // �O�[, ���[
		);
	return ConvertMatrix(mat);
}
Matrix4 YMath::MatPerspective()
{
	DirectX::XMMATRIX mat =
		DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(45.0f), // �㉺��p45�x
			(float)WinSize.x_ / WinSize.y_,		// �A�X�y�N�g�� (��ʉ���/��ʏc��)
			0.1f, 1000.0f						// �O�[, ���[
		);
	return ConvertMatrix(mat);
}
Matrix4 YMath::MatViewPort()
{
	Matrix4 result = Matrix4::Identity();

	result.m[0][0] = +WinSize.x_ / 2.0f;
	result.m[3][0] = +WinSize.x_ / 2.0f;
	result.m[1][1] = -WinSize.y_ / 2.0f;
	result.m[3][1] = +WinSize.y_ / 2.0f;
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
	float w = v.x_ * m.m[0][3] + v.y_ * m.m[1][3] + v.z_ * m.m[2][3] + m.m[3][3];
	Vector3 result
	{
		(v.x_ * m.m[0][0] + v.y_ * m.m[1][0] + v.z_ * m.m[2][0] + m.m[3][0]) / w,
		(v.x_ * m.m[0][1] + v.y_ * m.m[1][1] + v.z_ * m.m[2][1] + m.m[3][1]) / w,
		(v.x_ * m.m[0][2] + v.y_ * m.m[1][2] + v.z_ * m.m[2][2] + m.m[3][2]) / w
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
		v.x_ * m.m[0][0] + v.y_ * m.m[1][0] + v.z_ * m.m[2][0],
		v.x_ * m.m[0][1] + v.y_ * m.m[1][1] + v.z_ * m.m[2][1],
		v.x_ * m.m[0][2] + v.y_ * m.m[1][2] + v.z_ * m.m[2][2]
	};
	return result;
}

Vector4 YMath::MultVec4Mat4(const Vector4& v, const Matrix4& m)
{
	Vector4 result
	{
		v.r_ * m.m[0][0] + v.g_ * m.m[1][0] + v.b_ * m.m[2][0] + v.a_ * m.m[3][0],
		v.r_ * m.m[0][1] + v.g_ * m.m[1][1] + v.b_ * m.m[2][1] + v.a_ * m.m[3][1],
		v.r_ * m.m[0][2] + v.g_ * m.m[1][2] + v.b_ * m.m[2][2] + v.a_ * m.m[3][2],
		v.r_ * m.m[0][3] + v.g_ * m.m[1][3] + v.b_ * m.m[2][3] + v.a_ * m.m[3][3]
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

Vector3 YMath::AdjustAngle(const Vector3& velocity)
{
	Vector3 result{};
	result.y_ = std::atan2(velocity.x_, velocity.z_);
	Vector3 v = { velocity.x_, 0.0f, velocity.z_ };
	float xz = v.Length();
	result.x_ = std::atan2(-velocity.y_, xz);
	return result;
}
