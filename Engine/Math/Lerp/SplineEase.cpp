#include "SplineEase.h"
#include "Lerp.h"
#include "Vector2.h"
#include "Vector4.h"
#include <cassert>

using YMath::SplineEase;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;

template<typename T>
void SplineEase<T>::Initialize(const std::vector<T>& points, const float exponent)
{
	// 1つもないなら弾く
	assert(points.empty() == false);

	// 代入
	points_ = points;
	exponent_ = exponent;
}

template<typename T>
T SplineEase<T>::In(const float ratio) const { return SplineEaseIn<T>(points_, ratio, exponent_); }

template<typename T>
T SplineEase<T>::Out(const float ratio) const { return SplineEaseOut<T>(points_, ratio, exponent_); }

template<typename T>
T SplineEase<T>::InOut(const float ratio, const float controlPoint) const { return SplineEaseInOut<T>(points_, ratio, exponent_, controlPoint); }

template<typename T>
T SplineEase<T>::OutIn(const float ratio, const float controlPoint) const { return SplineEaseOutIn<T>(points_, ratio, exponent_, controlPoint); }

template<typename T>
SplineEase<T>::SplineEase(const std::vector<T>& points, const float exponent)
{
	Initialize(points, exponent);
}

template class SplineEase<float>;
template class SplineEase<double>;
template class SplineEase<Vector2>;
template class SplineEase<Vector3>;
template class SplineEase<Vector4>;