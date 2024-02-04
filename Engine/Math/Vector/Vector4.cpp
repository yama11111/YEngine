#include "Vector4.h"

using YMath::Vector4;

Vector4::Vector4() :
	x(0.0f), y(0.0f), z(0.0f), w(0.0f)
{}

Vector4::Vector4(float r, float g, float b, float a) :
	x(r), y(g), z(b), w(a)
{}

Vector4 Vector4::operator+() const
{
	return *this;
}
Vector4 Vector4::operator-() const
{
	return { -x, -y, -z, -w };
}

Vector4& Vector4::operator+=(const Vector4& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
	return *this;
}
Vector4& Vector4::operator-=(const Vector4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
	return *this;
}
Vector4& Vector4::operator*=(float s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}
Vector4& Vector4::operator/=(float s)
{
	x /= s;
	y /= s;
	z /= s;
	w /= s;
	return *this;
}

bool Vector4::operator==(const Vector4& v)
{
	return  (x == v.x && y == v.y && z == v.z && w == v.w);
}

bool Vector4::operator!=(const Vector4& v)
{
	return !(x == v.x && y == v.y && z == v.z && w == v.w);
}
