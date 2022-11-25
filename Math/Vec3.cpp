#include "Vec3.h"
#include <math.h>

using Math::Vec3;

Vec3::Vec3() :
	x_(0.0f), y_(0.0f), z_(0.0f)
{}

Vec3::Vec3(float x, float y, float z) :
	x_(x), y_(y), z_(z)
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
	return x_ == 0.0f && y_ == 0.0f && z_ == 0.0f;
}

constexpr float Vec3::Dot(const Vec3& v) const
{
	return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
}

Vec3 Vec3::Cross(const Vec3& v)
{
	return
	{
		y_ * v.z_ - z_ * v.y_,
		z_ * v.x_ - x_ * v.z_,
		x_ * v.y_ - y_ * v.x_
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
	return { -x_, -y_, -z_ };
}

Vec3& Vec3::operator+=(const Vec3& v)
{
	x_ += v.x_;
	y_ += v.y_;
	z_ += v.z_;
	return *this;
}
Vec3& Vec3::operator-=(const Vec3& v)
{
	x_ -= v.x_;
	y_ -= v.y_;
	z_ -= v.z_;
	return *this;
}
Vec3& Vec3::operator*=(float s)
{
	x_ *= s;
	y_ *= s;
	z_ *= s;
	return *this;
}
Vec3& Vec3::operator/=(float s)
{
	x_ /= s;
	y_ /= s;
	z_ /= s;
	return *this;
}

bool Vec3::operator==(const Vec3& v)
{
	return  (x_ == v.x_ && y_ == v.y_ && z_ == v.z_);
}

bool Vec3::operator!=(const Vec3& v)
{
	return !(x_ == v.x_ && y_ == v.y_ && z_ == v.z_);
}
