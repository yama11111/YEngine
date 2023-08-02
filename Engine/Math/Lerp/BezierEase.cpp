#include "BezierEase.h"
#include "Lerp.h"
#include "Vector2.h"
#include "Vector4.h"
#include <cassert>

using YMath::BezierEase;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;

template<typename T>
void BezierEase<T>::Initialize(const std::vector<T>& points, const float exponent)
{
	// 1‚Â‚à‚È‚¢‚È‚ç’e‚­
	assert(points.empty() == false);

	// ‘ã“ü
	points_ = points;
	exponent_ = exponent;
}

template<typename T>
T BezierEase<T>::In(const float ratio) { return BezierEaseIn<T>(points_, ratio, exponent_); }

template<typename T>
T BezierEase<T>::Out(const float ratio) { return BezierEaseOut<T>(points_, ratio, exponent_); }

template class BezierEase<float>;
template class BezierEase<double>;
template class BezierEase<Vector2>;
template class BezierEase<Vector3>;
template class BezierEase<Vector4>;