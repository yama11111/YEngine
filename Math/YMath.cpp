#include "YMath.h"
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

void Math::Srand() { srand(static_cast<unsigned int>(time(NULL))); }

int Math::GetRand(const int start, const int end)
{
	if (start == end) { return end; }

	int adjust = start < end ? 1 : -1;

	int div = end - start;
	if (div > 0) div++;
	if (div < 0) div--;

	return adjust * ((rand() % div) + start);
}

template<typename T>
T Math::Sign(const T num)
{
	if (num > 0) { return static_cast<T>(+1); }
	if (num < 0) { return static_cast<T>(-1); }
	return static_cast<T>(0);
}
template<>
float Math::Sign(const float num)
{
	if (num > 0.0f) { return (+1.0f); }
	if (num < 0.0f) { return (-1.0f); }
	return (0.0f);
}

template<typename T>
T Math::Clamp(const T num, const T lower, const T upper)
{
	return std::min(std::max(num, lower), upper);
}
template<>
float Math::Clamp(const float num, const float lower, const float upper)
{
	return std::fminf(std::fmaxf(num, lower), upper);
}
template<>
double Math::Clamp(const double num, const double lower, const double upper)
{
	return std::fmin(std::fmax(num, lower), upper);
}

Math::Vec4 Math::GetColor(const int R, const int G, const int B, const int A)
{
	Math::Vec4 result(
		static_cast<float>(Clamp(R, 0, 255)), 
		static_cast<float>(Clamp(G, 0, 255)), 
		static_cast<float>(Clamp(B, 0, 255)), 
		static_cast<float>(Clamp(A, 0, 255))
	);
	
	result.r_ /= 255.0f;
	result.g_ /= 255.0f;
	result.b_ /= 255.0f;
	result.a_ /= 255.0f;

	return result;
}

