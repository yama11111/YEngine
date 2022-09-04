#include "Vec4.h"

using Math::Vec4;

constexpr Vec4::Vec4() :
	r(0.0f), g(0.0f), b(0.0f), a(0.0f)
{}

constexpr Vec4::Vec4(const float r, const float g, const float b, const float a) :
	r(r), g(g), b(b), a(a)
{}