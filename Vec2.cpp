#include "Vec2.h"
#include <math.h>

constexpr Vec2::Vec2(const float x, const float y)
	:x(x), y(y)
{
}

float Vec2::Length() const
{
	return (float)sqrt(LengthSquare());
}

constexpr float Vec2::LengthSquare() const
{
	return Dot(*this);
}

Vec2 Vec2::Normalized() const
{
	if (!IsZero()) return *this / Length();
	return *this;
}

constexpr bool Vec2::IsZero() const
{
	return x == 0.0f && y == 0.0f;
}

constexpr float Vec2::Dot(const Vec2& v) const
{
	return x * v.x + y * v.y;
}

float Vec2::Distance(const Vec2& v) const
{
	return (v - *this).Length();
}

constexpr Vec2 Vec2::operator+() const
{
	return *this;
}
constexpr Vec2 Vec2::operator-() const
{
	return { -x,-y };
}
constexpr Vec2 Vec2::operator+(const Vec2& v) const
{
	return{ x + v.x, y + v.y };
}
constexpr Vec2 Vec2::operator-(const Vec2& v) const
{
	return{ x - v.x, y - v.y };
}
constexpr Vec2 Vec2::operator*(float s) const
{
	return{ x * s, y * s };
}
constexpr Vec2 Vec2::operator/(float s) const
{
	return{ x / s, y / s };
}

Vec2& Vec2::operator+=(const Vec2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}
Vec2& Vec2::operator-=(const Vec2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}
Vec2& Vec2::operator*=(float s)
{
	x *= s;
	y *= s;
	return *this;
}
Vec2& Vec2::operator/=(float s)
{
	x /= s;
	y /= s;
	return *this;
}

inline constexpr Vec2 operator*(float s, const Vec2& v)
{
	return { s * v.x, s * v.y };
}