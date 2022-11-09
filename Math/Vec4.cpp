#include "Vec4.h"

using Math::Vec4;

Vec4::Vec4() :
	r_(0.0f), g_(0.0f), b_(0.0f), a_(0.0f)
{}

Vec4::Vec4(float r, float g, float b, float a) :
	r_(r), g_(g), b_(b), a_(a)
{}