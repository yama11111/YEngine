#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4.h"

#define PI 3.141592f

namespace YMath
{
#pragma region 変換系
	
	// ------------ アフィン変換 ------------ //
	
	// 拡縮変換
	Matrix4 MatScale(const Vector3& s);
	
	// X軸回転変換
	Matrix4 MatRotationX(float angle);
	// Y軸回転変換
	Matrix4 MatRotationY(float angle);
	// Z軸回転変換
	Matrix4 MatRotationZ(float angle);
	// 回転変換(Z→X→Y)
	Matrix4 MatRotation(const Vector3& r);

	// 座標変換
	Matrix4 MatTranslation(const Vector3& t);
	
	// ----- ビュープロジェクション変換 ----- //
	
	// 平行投影変換行列
	Matrix4 MatOrthoGraphic();
	// 透視投影変換行列
	Matrix4 MatPerspective();
	// ビューポート行列
	Matrix4 MatViewPort();
	// ビュー行列(左手座標系)
	Matrix4 MatLookAtLH(const Vector3& eye, const Vector3& target, const Vector3& up);
	
#pragma endregion

	Vector3 MatTransform(const Vector3& v, const Matrix4& m);
	Vector3 operator*(const Vector3& v, const Matrix4& m);

	// Vector3 * Matrix4
	Vector3 MultVec3Mat4(const Vector3& v, const Matrix4& m);
	// Vector4 * Matrix4
	Vector4 MultVec4Mat4(const Vector4& v, const Matrix4& m);
	// 逆行列
	Matrix4 InverceMat4(const Matrix4& m);

	// 2D座標→3D座標
	Vector3 WorldPos(const Vector2& screen, float z, const Matrix4& view, const Matrix4& projection);

	// 角度調整
	Vector3 AdjustAngle(const Vector3& velocity);
}