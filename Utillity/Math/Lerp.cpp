#include "Lerp.h"
#include <math.h>
#include <cassert>

using YMath::Ease;
using YMath::BezierEase;
using YMath::Vector2;
using YMath::Vector3;

template<typename T>
T YMath::Lerp(const T& a, const T& b, const float t)
{
	return static_cast<T>(a + t * (b - a));
}
Vector3 YMath::Slerp(const Vector3& v1, const Vector3& v2, float t)
{
	float dot = v1.Dot(v2);
	if (dot >= 1.0 || dot <= -1.0) return v1;

	float theta = acosf(dot);
	float sTheta = sinf(theta);
	float sf = sinf((1 - t) * theta);
	float st = sinf(t * theta);

	float aS = v1.Length();
	float bS = v2.Length();
	float s = aS + t * (bS - aS);

	Vector3 from = v1 * sf;
	Vector3 to = v2 * st / sTheta;
	Vector3 result = (from + to) * s;
	return result;
}
template<typename T>
T YMath::EaseIn(const T& start, const T& end, const float time, const float power)
{
	return Lerp<T>(start, end, powf(time, power));
}
template<typename T>
T YMath::EaseOut(const T& start, const T& end, const float time, const float power)
{
	return Lerp<T>(start, end, 1 - powf(1 - time, power));
}

Vector3 YMath::Bezier(const std::vector<Vector3>& points, const float time)
{
	assert(!points.empty());

	if (points.size() == 1) { return points[0]; }
	if (points.size() == 2) { return Lerp(points[0], points[1], time); }

	std::vector<Vector3> p = points, result;
	while (true)
	{
		result.clear();
		for (size_t i = 0; i < p.size() - 1; i++)
		{
			result.push_back(Lerp(p[i], p[i + 1], time));
		}
		if (result.size() <= 2) { break; }
		p = result;
	}

	return Lerp(result[0], result[1], time);
}
Vector3 YMath::Spline(const std::vector<Vector3>& points, const size_t section, const float time)
{
	assert(4 <= points.size());

	size_t n = points.size() - 4;
	if (section > n) { return points[n]; }
	if (section < 0) { return points[1]; }

	Vector3 p0 = points[section];
	Vector3 p1 = points[section + 1];
	Vector3 p2 = points[section + 2];
	Vector3 p3 = points[section + 3];

	Vector3 position =
		0.5f * ((2 * p1) + (-p0 + p2) * time
			+ ((2 * p0) - (5 * p1) + (4 * p2) - p3) * powf(time, 2.0f)
			+ (-p0 + (3 * p1) - (3 * p2) + p3) * powf(time, 3.0f));

	return position;
}

Vector3 YMath::EaseInBezier(const std::vector<Vector3>& points, const float time, const float power)
{
	return Bezier(points, powf(time, power));
}
Vector3 YMath::EaseOutBezier(const std::vector<Vector3>& points, const float time, const float power)
{
	return Bezier(points, 1 - powf(1 - time, power));
}
//Vector3 Math::EaseInSpline(const std::vector<Vector3>& points, const size_t section, const float time, const float power)
//{
//	return Spline(points, section, powf(time, power));
//}
//Vector3 Math::EaseOutSpline(const std::vector<Vector3>& points, const size_t section, const float time, const float power)
//{
//	return Spline(points, section, 1 - powf(1 - time, power));
//}

template<typename T>
void Ease<T>::Initialize(const T& start, const T& end, const float power)
{
	start_ = start;
	end_ = end;
	power_ = power;
}

template<typename T>
T Ease<T>::In(const float time) { return EaseIn<T>(start_, end_, time, power_); }

template<typename T>
T Ease<T>::Out(const float time) { return EaseOut<T>(start_, end_, time, power_); }

template class Ease<int>;
template class Ease<float>;
template class Ease<double>;
template class Ease<Vector2>;
template class Ease<Vector3>;

void BezierEase::Initialize(const std::vector<Vector3>& points, const float power)
{
	assert(!points.empty());

	points_ = points;
	power_ = power;
}

Vector3 BezierEase::In(const float time)
{
	return EaseInBezier(points_, time, power_);
}
Vector3 BezierEase::Out(const float time)
{
	return EaseOutBezier(points_, time, power_);
}

