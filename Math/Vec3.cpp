#include "Vec3.h"
#include <math.h>

using Math::Vec3;

Vec3::Vec3() :
	x(0.0f), y(0.0f), z(0.0f)
{}

Vec3::Vec3(float x, float y, float z) :
	x(x), y(y), z(z)
{}

float Vec3::Length() const
{
	return (float)sqrt(LengthSquare());
}

constexpr float Vec3::LengthSquare() const
{
	return Dot(*this);
}

Vec3 Vec3::Normalized() const
{
	if (!IsZero()) return *this / Length();
	return *this;
}

constexpr bool Vec3::IsZero() const
{
	return x == 0.0f && y == 0.0f && z == 0.0f;
}

constexpr float Vec3::Dot(const Vec3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

Vec3 Vec3::Cross(const Vec3& v)
{
	return
	{
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
	};
}

float Vec3::Distance(const Vec3& v) const
{
	return (v - *this).Length();
}

Vec3 Vec3::operator+() const
{
	return *this;
}
Vec3 Vec3::operator-() const
{
	return { -x, -y, -z };
}

Vec3& Vec3::operator+=(const Vec3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
Vec3& Vec3::operator-=(const Vec3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
Vec3& Vec3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}
Vec3& Vec3::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

inline Vec3 Math::operator+(const Vec3& v1, const Vec3& v2)
{
	return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
}
inline Vec3 Math::operator-(const Vec3& v1, const Vec3& v2)
{
	return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
}
inline Vec3 Math::operator*(const Vec3& v, float s)
{
	return { v.x * s, v.y * s, v.z * s };
}
inline Vec3 Math::operator*(float s, const Vec3& v)
{
	return { s * v.x, s * v.y, s * v.z };
}
inline Vec3 Math::operator/(const Vec3& v, float s)
{
	return { v.x / s, v.y / s, v.z / s };
}
