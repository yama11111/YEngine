#include "MathUtil.h"
#include <cmath>
#include <algorithm>
#include <cstdlib>
#include <cstdint>
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

Vector3 YMath::GetRand(const Vector3& start, const Vector3& end, const float place)
{
	return Vector3(
		GetRand(start.x, end.x, place),
		GetRand(start.y, end.y, place),
		GetRand(start.z, end.z, place)
	);
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
bool YMath::InRange(const T& num, const T& lower, const T& upper)
{
	return (lower < num && num < upper);
}
template<>
bool YMath::InRange(const Vector3& num, const Vector3& lower, const Vector3& upper)
{
	return bool(
		InRange(num.x, lower.x, upper.x) &&
		InRange(num.y, lower.y, upper.y) &&
		InRange(num.z, lower.z, upper.z));
}
template<typename T>
bool YMath::InRange(const T& num, const T& lower, const T& upper, bool& isOverLower, bool& isOverUpper)
{
	isOverLower = num < lower;
	isOverUpper = upper < num;

	return (isOverLower || isOverUpper) == false;
}
template<>
bool YMath::InRange(const float& num, const float& lower, const float& upper, bool& isOverLower, bool& isOverUpper)
{
	isOverLower = num < lower;
	isOverUpper = upper < num;

	return (isOverLower || isOverUpper) == false;
}

template<typename T>
T YMath::Abs(const T& num)
{
	return std::abs(num);
}
template<>
float YMath::Abs(const float& num)
{
	return std::fabs(num);
}
template<>
Vector3 YMath::Abs(const Vector3& num)
{
	return YMath::Vector3(
		std::fabs(num.x),
		std::fabs(num.y),
		std::fabs(num.z));
}

template<typename T>
T YMath::Clamp(const T& num, const T& lower, const T& upper)
{
	return std::min(std::max(num, lower), upper);
}
template<>
uint32_t YMath::Clamp(const uint32_t& num, const uint32_t& lower, const uint32_t& upper)
{
	return std::min(std::max(num, lower), upper);
}
template<>
float YMath::Clamp(const float& num, const float& lower, const float& upper)
{
	return std::fminf(std::fmaxf(num, lower), upper);
}
template<>
double YMath::Clamp(const double& num, const double& lower, const double& upper)
{
	return std::fmin(std::fmax(num, lower), upper);
}
template<>
YMath::Vector3 YMath::Clamp(const YMath::Vector3& num, const YMath::Vector3& lower, const YMath::Vector3& upper)
{
	Vector3 result;

	result.x = std::fminf(std::fmaxf(num.x, lower.x), upper.x);
	result.y = std::fminf(std::fmaxf(num.y, lower.y), upper.y);
	result.z = std::fminf(std::fmaxf(num.z, lower.z), upper.z);

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
	
	result.x /= 255.0f;
	result.y /= 255.0f;
	result.z /= 255.0f;
	result.w /= 255.0f;

	return result;
}

float YMath::ConvertFromDegreeToRadian(const float degree)
{
	return degree * (kPI / 180.0f);
}

Vector3 YMath::ConvertFromDegreeToRadian(const Vector3& degree)
{
	return Vector3(
		ConvertFromDegreeToRadian(degree.x), 
		ConvertFromDegreeToRadian(degree.y),
		ConvertFromDegreeToRadian(degree.z));
}

