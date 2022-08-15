#pragma once
#include "Mat4.h"
#include "Vec3.h"

Mat4 MatScale(const Vec3& s);

Mat4 MatRotateX(float angle);
Mat4 MatRotateY(float angle);
Mat4 MatRotateZ(float angle);

Mat4 MatTranslate(const Vec3& t);

Vec3 MatTransform(const Vec3& v, const Mat4& m);
Vec3 operator*(const Vec3& v, const Mat4& m);
