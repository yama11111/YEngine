#include "Vector2.h"
#include <math.h>

using YMath::Vector2;

Vector2::Vector2() :
	x(0.0f), y(0.0f)
{}

Vector2::Vector2(float x, float y)
	:x(x), y(y)
{}

float Vector2::Length() const
{
	return (float)sqrt(LengthSquare());
}

constexpr float Vector2::LengthSquare() const
{
	return Dot(*this);
}

Vector2 Vector2::Normalized() const
{
	if (!IsZero()) return *this / Length();
	return *this;
}

constexpr bool Vector2::IsZero() const
{
	return x == 0.0f && y == 0.0f;
}

constexpr float Vector2::Dot(const Vector2& v) const
{
	return x * v.x + y * v.y;
}

float Vector2::Distance(const Vector2& v) const
{
	return (v - *this).Length();
}

Vector2 Vector2::operator+() const
{
	return *this;
}
Vector2 Vector2::operator-() const
{
	return { -x,-y };
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}
Vector2& Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}
Vector2& Vector2::operator*=(float s)
{
	x *= s;
	y *= s;
	return *this;
}
Vector2& Vector2::operator/=(float s)
{
	x /= s;
	y /= s;
	return *this;
}

bool Vector2::operator==(const Vector2& v)
{
	return  (x == v.x && y == v.y);
}

bool Vector2::operator!=(const Vector2& v)
{
	return !(x == v.x && y == v.y);
}
