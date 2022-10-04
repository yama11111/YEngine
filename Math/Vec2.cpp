#include "Vec2.h"
#include <math.h>

using Math::Vec2;

Vec2::Vec2() :
	x(0.0f), y(0.0f)
{}

Vec2::Vec2(float x, float y)
	:x(x), y(y)
{}

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

Vec2 Vec2::operator+() const
{
	return *this;
}
Vec2 Vec2::operator-() const
{
	return { -x,-y };
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

inline Vec2 Math::operator+(const Vec2& v1, const Vec2& v2)
{
	return{ v1.x + v2.x, v1.y + v2.y };
}
inline Vec2 Math::operator-(const Vec2& v1, const Vec2& v2)
{
	return{ v1.x - v2.x, v1.y - v2.y };
}
inline Vec2 Math::operator*(const Vec2& v, float s)
{
	return{ v.x * s, v.y * s };
}
inline Vec2 Math::operator*(float s, const Vec2& v)
{
	return { s * v.x, s * v.y };
}
inline Vec2 Math::operator/(const Vec2& v, float s)
{
	return{ v.x / s, v.y / s };
}
