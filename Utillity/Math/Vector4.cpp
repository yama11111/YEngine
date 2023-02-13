#include "Vector4.h"

using YMath::Vector4;

Vector4::Vector4() :
	r_(0.0f), g_(0.0f), b_(0.0f), a_(0.0f)
{}

Vector4::Vector4(float r, float g, float b, float a) :
	r_(r), g_(g), b_(b), a_(a)
{}

Vector4 Vector4::operator+() const
{
	return *this;
}
Vector4 Vector4::operator-() const
{
	return { -r_, -g_, -b_, -a_ };
}

Vector4& Vector4::operator+=(const Vector4& v)
{
	r_ += v.r_;
	g_ += v.g_;
	b_ += v.b_;
	a_ += v.a_;
	return *this;
}
Vector4& Vector4::operator-=(const Vector4& v)
{
	r_ -= v.r_;
	g_ -= v.g_;
	b_ -= v.b_;
	a_ -= v.a_;
	return *this;
}
Vector4& Vector4::operator*=(float s)
{
	r_ *= s;
	g_ *= s;
	b_ *= s;
	a_ *= s;
	return *this;
}
Vector4& Vector4::operator/=(float s)
{
	r_ /= s;
	g_ /= s;
	b_ /= s;
	a_ /= s;
	return *this;
}

bool Vector4::operator==(const Vector4& v)
{
	return  (r_ == v.r_ && g_ == v.g_ && b_ == v.b_ && a_ == v.a_);
}

bool Vector4::operator!=(const Vector4& v)
{
	return !(r_ == v.r_ && g_ == v.g_ && b_ == v.b_ && a_ == v.a_);
}
