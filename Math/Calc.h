#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat4.h"
#define PI 3.141592f

namespace Math
{
	// 拡縮変換
	Mat4 MatScale(const Vec3& s);
	
	// X軸回転変換
	Mat4 MatRotationX(float angle);
	// Y軸回転変換
	Mat4 MatRotationY(float angle);
	// Z軸回転変換
	Mat4 MatRotationZ(float angle);
	// 回転変換(Z→X→Y)
	Mat4 MatRotation(const Vec3& r);

	// 座標変換
	Mat4 MatTranslation(const Vec3& t);

	Vec3 MatTransform(const Vec3& v, const Mat4& m);
	Vec3 operator*(const Vec3& v, const Mat4& m);

	// Vector3 * Matrix4
	Vec3 MultVec3Mat4(const Vec3& v, const Mat4& m);
	// Vector4 * Matrix4
	Vec4 MultVec4Mat4(const Vec4& v, const Mat4& m);
	// 逆行列
	Mat4 InverceMat4(const Mat4& m);

	// 平行投影変換行列
	Mat4 MatOrthoGraphic();
	// 透視投影変換行列
	Mat4 MatPerspective();
	// ビューポート行列
	Mat4 MatViewPort();
	// ビュー行列(左手座標系)
	Mat4 MatLookAtLH(const Vec3& eye, const Vec3& target, const Vec3& up);

	// 2D座標→3D座標
	Vec3 WorldPos(const Vec2& screen, float z, const Mat4& view, const Mat4& projection);

	// 角度調整
	Vec3 AdjustAngle(Vec3& velocity);

	float Lerp(const float a, const float b, const float t);

	Vec3 Lerp(const Vec3& v1, const Vec3& v2, float t);
	Vec3 Slerp(const Vec3& v1, const Vec3& v2, float t);
	
	// 色変換((0～255)→(0.0～1.0))
	Vec4 GetColor(const Vec4& color);
	
	// アタリ判定(線×球)
	bool CollRaySphere(
		const Vec3& ray, const Vec3& velocity,
		const Vec3& sphere, const float rad);
	
	// アタリ判定(線×球) <貫通点取得ver>
	bool CollRaySphere(
		const Vec3& ray, const Vec3& velocity,
		const Vec3& sphere, const float rad,
		Vec3& start, Vec3& end);
}