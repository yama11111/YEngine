#include "Vector3.h"
#include <math.h>

using YMath::Vector3;

Vector3::Vector3() :
	x(0.0f), y(0.0f), z(0.0f)
{}

Vector3::Vector3(float x, float y, float z) :
	x(x), y(y), z(z)
{}

float Vector3::Length() const
{
	return static_cast<float>(sqrt(LengthSquare()));
}

constexpr float Vector3::LengthSquare() const
{
	return Dot(*this);
}

Vector3 Vector3::Normalized() const
{
	if (!IsZero()) { return *this / Length(); }
	return *this;
}

constexpr bool Vector3::IsZero() const
{
	return x == 0.0f && y == 0.0f && z == 0.0f;
}

constexpr float Vector3::Dot(const Vector3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::Cross(const Vector3& v) const
{
	return
	{
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x
	};
}

float Vector3::Distance(const Vector3& v) const
{
	return (v - *this).Length();
}

Vector3 Vector3::operator+() const
{
	return *this;
}
Vector3 Vector3::operator-() const
{
	return { -x, -y, -z };
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
Vector3& Vector3::operator-=(const Vector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}
Vector3& Vector3::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}
Vector3& Vector3::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

bool Vector3::operator==(const Vector3& v)
{
	return  (x == v.x && y == v.y && z == v.z);
}

bool Vector3::operator!=(const Vector3& v)
{
	return !(x == v.x && y == v.y && z == v.z);
}
