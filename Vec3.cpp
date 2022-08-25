#include "Vec3.h"
#include <math.h>

constexpr Vec3::Vec3(const float x, const float y, const float z) :
	x(x), y(y), z(z)
{
}

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

constexpr Vec3 Vec3::operator+() const
{
	return *this;
}
constexpr Vec3 Vec3::operator-() const
{
	return { -x, -y, -z };
}
constexpr Vec3 Vec3::operator+(const Vec3& v) const
{
	return { x + v.x, y + v.y, z + v.z };
}
constexpr Vec3 Vec3::operator-(const Vec3& v) const
{
	return { x - v.x, y - v.y, z - v.z };
}
constexpr Vec3 Vec3::operator*(float s) const
{
	return { x * s, y * s, z * s };
}
constexpr Vec3 Vec3::operator/(float s) const
{
	return { x / s, y / s, z / s };
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

inline constexpr Vec3 operator*(float s, const Vec3& v)
{
	return { s * v.x, s * v.y, s * v.z };
}
