#include "Lerp.h"
#include <math.h>

using::Math::Ease;
using::Math::Vec2;
using::Math::Vec3;

template<typename T>
T Math::Lerp(const T& a, const T& b, const float t)
{
	return static_cast<T>(a + t * (b - a));
}
Vec3 Math::Slerp(const Vec3& v1, const Vec3& v2, float t)
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

	Vec3 from = v1 * sf;
	Vec3 to = v2 * st / sTheta;
	Vec3 result = (from + to) * s;
	return result;
}
template<typename T>
T Math::EaseIn(const T& start, const T& end, const float time, const float power)
{
	return Lerp<T>(start, end, powf(time, power));
}
template<typename T>
T Math::EaseOut(const T& start, const T& end, const float time, const float power)
{
	return Lerp<T>(start, end, 1 - powf(1 - time, power));
}

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
template class Ease<Vec2>;
template class Ease<Vec3>;