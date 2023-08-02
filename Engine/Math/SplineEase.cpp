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
	// 1‚Â‚à‚È‚¢‚È‚ç’e‚­
	assert(points.empty() == false);

	// ‘ã“ü
	points_ = points;
	exponent_ = exponent;
}

template<typename T>
T SplineEase<T>::In(const float ratio) { return SplineEaseIn<T>(points_, ratio, exponent_); }

template<typename T>
T SplineEase<T>::Out(const float ratio) { return SplineEaseOut<T>(points_, ratio, exponent_); }

template class SplineEase<float>;
template class SplineEase<double>;
template class SplineEase<Vector2>;
template class SplineEase<Vector3>;
template class SplineEase<Vector4>;