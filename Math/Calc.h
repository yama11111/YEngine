#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"
#include "Mat4.h"
#define PI 3.141592f

namespace Math
{
	// Šgk•ÏŠ·
	Mat4 MatScale(const Vec3& s);
	
	// X²‰ñ“]•ÏŠ·
	Mat4 MatRotationX(float angle);
	// Y²‰ñ“]•ÏŠ·
	Mat4 MatRotationY(float angle);
	// Z²‰ñ“]•ÏŠ·
	Mat4 MatRotationZ(float angle);
	// ‰ñ“]•ÏŠ·(Z¨X¨Y)
	Mat4 MatRotation(const Vec3& r);

	// À•W•ÏŠ·
	Mat4 MatTranslation(const Vec3& t);

	Vec3 MatTransform(const Vec3& v, const Mat4& m);
	Vec3 operator*(const Vec3& v, const Mat4& m);

	// Vector3 * Matrix4
	Vec3 MultVec3Mat4(const Vec3& v, const Mat4& m);
	// Vector4 * Matrix4
	Vec4 MultVec4Mat4(const Vec4& v, const Mat4& m);
	// ‹ts—ñ
	Mat4 InverceMat4(const Mat4& m);

	// Ë‰e•ÏŠ·s—ñ
	Mat4 MatOrthoGraphic();
	// “§‹“Š‰e•ÏŠ·s—ñ
	Mat4 MatPerspective();
	// ƒrƒ…[ƒ|[ƒgs—ñ
	Mat4 MatViewPort();
	// ƒrƒ…[s—ñ(¶èÀ•WŒn)
	Mat4 MatLookAtLH(const Vec3& eye, const Vec3& target, const Vec3& up);

	// 2DÀ•W¨3DÀ•W
	Vec3 WorldPos(const Vec2& screen, float z, const Mat4& view, const Mat4& projection);

	// Šp“x’²®
	Vec3 AdjustAngle(Vec3& velocity);

	float Lerp(const float a, const float b, const float t);

	Vec3 Lerp(const Vec3& v1, const Vec3& v2, float t);
	Vec3 Slerp(const Vec3& v1, const Vec3& v2, float t);
	
	// F•ÏŠ·((0`255)¨(0.0`1.0))
	Vec4 GetColor(const Vec4& color);
	
	// ƒAƒ^ƒŠ”»’è(ü~‹…)
	bool CollRaySphere(
		const Vec3& ray, const Vec3& velocity,
		const Vec3& sphere, const float rad);
	
	// ƒAƒ^ƒŠ”»’è(ü~‹…) <ŠÑ’Ê“_æ“¾ver>
	bool CollRaySphere(
		const Vec3& ray, const Vec3& velocity,
		const Vec3& sphere, const float rad,
		Vec3& start, Vec3& end);
}