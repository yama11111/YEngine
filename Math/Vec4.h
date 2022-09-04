#pragma once

namespace Math
{
	struct Vec4
	{
	public:
		float r;
		float g;
		float b;
		float a;
	public:
		constexpr Vec4();
		constexpr Vec4(const float r, const float g, const float b, const float a);
	};
}
