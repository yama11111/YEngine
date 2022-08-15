#pragma once
#include "Mat4.h"
#include "Vec3.h"

Mat4 MatScale(const Vec3& s);

Mat4 MatRotationX(float angle);
Mat4 MatRotationY(float angle);
Mat4 MatRotationZ(float angle);

Mat4 MatRotation(const Vec3& r);

Mat4 MatTranslation(const Vec3& t);

Vec3 MatTransform(const Vec3& v, const Mat4& m);
Vec3 operator*(const Vec3& v, const Mat4& m);

Mat4 MatOrthoGraphic();
Mat4 MatPerspective();

Mat4 MatLookAtLH(const Vec3& eye, const Vec3& target, const Vec3& up);