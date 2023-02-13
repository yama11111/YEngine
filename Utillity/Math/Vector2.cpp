#include "Vector2.h"
#include <math.h>

using YMath::Vector2;

Vector2::Vector2() :
	x_(0.0f), y_(0.0f)
{}

Vector2::Vector2(float x, float y)
	:x_(x), y_(y)
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
	return x_ == 0.0f && y_ == 0.0f;
}

constexpr float Vector2::Dot(const Vector2& v) const
{
	return x_ * v.x_ + y_ * v.y_;
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
	return { -x_,-y_ };
}

Vector2& Vector2::operator+=(const Vector2& v)
{
	x_ += v.x_;
	y_ += v.y_;
	return *this;
}
Vector2& Vector2::operator-=(const Vector2& v)
{
	x_ -= v.x_;
	y_ -= v.y_;
	return *this;
}
Vector2& Vector2::operator*=(float s)
{
	x_ *= s;
	y_ *= s;
	return *this;
}
Vector2& Vector2::operator/=(float s)
{
	x_ /= s;
	y_ /= s;
	return *this;
}

bool Vector2::operator==(const Vector2& v)
{
	return  (x_ == v.x_ && y_ == v.y_);
}

bool Vector2::operator!=(const Vector2& v)
{
	return !(x_ == v.x_ && y_ == v.y_);
}
