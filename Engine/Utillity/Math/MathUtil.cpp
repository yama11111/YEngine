#include "MathUtil.h"
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include "Def.h"

using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;

void YMath::Srand() { srand(static_cast<unsigned int>(time(NULL))); }

int YMath::GetRand(const int start, const int end)
{
	if (start == end) { return end; }

	int adjust = start < end ? 1 : -1;

	int div = end - start;
	if (div > 0) div++;
	if (div < 0) div--;

	return adjust * ((rand() % div) + start);
}

float YMath::GetRand(const float start, const float end, const float place)
{
	int s = static_cast<int>(start * place);
	int e = static_cast<int>(end * place);

	return static_cast<float>(GetRand(s, e)) / place;
}

template<typename T>
T YMath::Sign(const T num)
{
	if (num > 0) { return static_cast<T>(+1); }
	if (num < 0) { return static_cast<T>(-1); }
	return static_cast<T>(0);
}
template<>
float YMath::Sign(const float num)
{
	if (num > 0.0f) { return (+1.0f); }
	if (num < 0.0f) { return (-1.0f); }
	return (0.0f);
}

template<typename T>
T YMath::Clamp(const T num, const T lower, const T upper)
{
	return std::min(std::max(num, lower), upper);
}
template<>
float YMath::Clamp(const float num, const float lower, const float upper)
{
	return std::fminf(std::fmaxf(num, lower), upper);
}
template<>
double YMath::Clamp(const double num, const double lower, const double upper)
{
	return std::fmin(std::fmax(num, lower), upper);
}
template<>
YMath::Vector3 YMath::Clamp(const YMath::Vector3 num, const YMath::Vector3 lower, const YMath::Vector3 upper)
{
	Vector3 result;

	result.x_ = std::fminf(std::fmaxf(num.x_, lower.x_), upper.x_);
	result.y_ = std::fminf(std::fmaxf(num.y_, lower.y_), upper.y_);
	result.z_ = std::fminf(std::fmaxf(num.z_, lower.z_), upper.z_);

	return result;
}

YMath::Vector4 YMath::GetColor(const int R, const int G, const int B, const int A)
{
	YMath::Vector4 result(
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

float YMath::ConvertFromDegreeToRadian(const float degree)
{
	return degree * (PI / 180.0f);
}

Vector3 YMath::ConvertFromDegreeToRadian(const Vector3& degree)
{
	return Vector3(
		ConvertFromDegreeToRadian(degree.x_), 
		ConvertFromDegreeToRadian(degree.y_),
		ConvertFromDegreeToRadian(degree.z_));
}

