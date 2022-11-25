#include "Vec2.h"
#include <math.h>

using Math::Vec2;

Vec2::Vec2() :
	x_(0.0f), y_(0.0f)
{}

Vec2::Vec2(float x, float y)
	:x_(x), y_(y)
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
	return x_ == 0.0f && y_ == 0.0f;
}

constexpr float Vec2::Dot(const Vec2& v) const
{
	return x_ * v.x_ + y_ * v.y_;
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
	return { -x_,-y_ };
}

Vec2& Vec2::operator+=(const Vec2& v)
{
	x_ += v.x_;
	y_ += v.y_;
	return *this;
}
Vec2& Vec2::operator-=(const Vec2& v)
{
	x_ -= v.x_;
	y_ -= v.y_;
	return *this;
}
Vec2& Vec2::operator*=(float s)
{
	x_ *= s;
	y_ *= s;
	return *this;
}
Vec2& Vec2::operator/=(float s)
{
	x_ /= s;
	y_ /= s;
	return *this;
}

bool Vec2::operator==(const Vec2& v)
{
	return  (x_ == v.x_ && y_ == v.y_);
}

bool Vec2::operator!=(const Vec2& v)
{
	return !(x_ == v.x_ && y_ == v.y_);
}
