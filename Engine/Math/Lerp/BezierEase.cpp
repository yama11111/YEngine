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
	// 1つもないなら弾く
	assert(points.empty() == false);

	// 代入
	points_ = points;
	exponent_ = exponent;
}

template<typename T>
T BezierEase<T>::In(const float ratio) const { return BezierEaseIn<T>(points_, ratio, exponent_); }

template<typename T>
T BezierEase<T>::Out(const float ratio) const { return BezierEaseOut<T>(points_, ratio, exponent_); }

template<typename T>
T BezierEase<T>::InOut(const float ratio, const float controlPoint) const { return BezierEaseInOut<T>(points_, ratio, exponent_, controlPoint); }

template<typename T>
T BezierEase<T>::OutIn(const float ratio, const float controlPoint) const { return BezierEaseOutIn<T>(points_, ratio, exponent_, controlPoint); }

template<typename T>
BezierEase<T>::BezierEase(const std::vector<T>& points, const float exponent)
{
	Initialize(points, exponent);
}

template class BezierEase<float>;
template class BezierEase<double>;
template class BezierEase<Vector2>;
template class BezierEase<Vector3>;
template class BezierEase<Vector4>;