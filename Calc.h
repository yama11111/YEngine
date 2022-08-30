#pragma once
#include "Vec2.h"
#include "Vec4.h"
#include "MatViewProjection.h"
#define PI 3.141592f

Mat4 MatScale(const Vec3& s);

Mat4 MatRotationX(float angle);
Mat4 MatRotationY(float angle);
Mat4 MatRotationZ(float angle);
Mat4 MatRotation(const Vec3& r);

Mat4 MatTranslation(const Vec3& t);

Vec3 MatTransform(const Vec3& v, const Mat4& m);
Vec3 operator*(const Vec3& v, const Mat4& m);

Vec3 MultVec3Mat4(const Vec3& v, const Mat4& m);
Vec4 MultVec4Mat4(const Vec4& v, const Mat4& m);
Mat4 InverceMat4(const Mat4& m);

Mat4 MatOrthoGraphic();
Mat4 MatPerspective();
Mat4 MatViewPort();

Mat4 MatLookAtLH(const Vec3& eye, const Vec3& target, const Vec3& up);

Vec3 WorldPos(const Vec2& screen, float z, const MatViewProjection& vp);

Vec3 AdjustAngle(Vec3& velocity);

Vec3 Lerp (const Vec3& v1, const Vec3& v2, float t);
Vec3 Slerp(const Vec3& v1, const Vec3& v2, float t);

float lerp(const float a, const float b, const float t);
float EaseIn(const float start, const float end, const float time, const float power);
float EaseOut(const float start, const float end, const float time, const float power);

Vec4 GetColor(const Vec4& color);

bool CollRaySphere(	const Vec3& ray, const Vec3& velocity,
					const Vec3& sphere, const float rad, Vec3& start);