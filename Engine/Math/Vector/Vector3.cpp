#include "Vector3.h"
#include <math.h>

using YMath::Vector3;

Vector3::Vector3() :
	x_(0.0f), y_(0.0f), z_(0.0f)
{}

Vector3::Vector3(float x, float y, float z) :
	x_(x), y_(y), z_(z)
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
	return x_ == 0.0f && y_ == 0.0f && z_ == 0.0f;
}

constexpr float Vector3::Dot(const Vector3& v) const
{
	return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
}

Vector3 Vector3::Cross(const Vector3& v) const
{
	return
	{
		y_ * v.z_ - z_ * v.y_,
		z_ * v.x_ - x_ * v.z_,
		x_ * v.y_ - y_ * v.x_
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
	return { -x_, -y_, -z_ };
}

Vector3& Vector3::operator+=(const Vector3& v)
{
	x_ += v.x_;
	y_ += v.y_;
	z_ += v.z_;
	return *this;
}
Vector3& Vector3::operator-=(const Vector3& v)
{
	x_ -= v.x_;
	y_ -= v.y_;
	z_ -= v.z_;
	return *this;
}
Vector3& Vector3::operator*=(float s)
{
	x_ *= s;
	y_ *= s;
	z_ *= s;
	return *this;
}
Vector3& Vector3::operator/=(float s)
{
	x_ /= s;
	y_ /= s;
	z_ /= s;
	return *this;
}

bool Vector3::operator==(const Vector3& v)
{
	return  (x_ == v.x_ && y_ == v.y_ && z_ == v.z_);
}

bool Vector3::operator!=(const Vector3& v)
{
	return !(x_ == v.x_ && y_ == v.y_ && z_ == v.z_);
}
