#include "Vec4.h"

using Math::Vec4;

Vec4::Vec4() :
	r_(0.0f), g_(0.0f), b_(0.0f), a_(0.0f)
{}

Vec4::Vec4(float r, float g, float b, float a) :
	r_(r), g_(g), b_(b), a_(a)
{}

Vec4 Vec4::operator+() const
{
	return *this;
}
Vec4 Vec4::operator-() const
{
	return { -r_, -g_, -b_, -a_ };
}

Vec4& Vec4::operator+=(const Vec4& v)
{
	r_ += v.r_;
	g_ += v.g_;
	b_ += v.b_;
	a_ += v.a_;
	return *this;
}
Vec4& Vec4::operator-=(const Vec4& v)
{
	r_ -= v.r_;
	g_ -= v.g_;
	b_ -= v.b_;
	a_ -= v.a_;
	return *this;
}
Vec4& Vec4::operator*=(float s)
{
	r_ *= s;
	g_ *= s;
	b_ *= s;
	a_ *= s;
	return *this;
}
Vec4& Vec4::operator/=(float s)
{
	r_ /= s;
	g_ /= s;
	b_ /= s;
	a_ /= s;
	return *this;
}

bool Vec4::operator==(const Vec4& v)
{
	return  (r_ == v.r_ && g_ == v.g_ && b_ == v.b_ && a_ == v.a_);
}

bool Vec4::operator!=(const Vec4& v)
{
	return !(r_ == v.r_ && g_ == v.g_ && b_ == v.b_ && a_ == v.a_);
}
