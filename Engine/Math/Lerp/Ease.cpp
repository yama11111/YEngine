#include "Ease.h"
#include "Lerp.h"
#include "Vector2.h"
#include "Vector4.h"

using YMath::Ease;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;

template<typename T>
void Ease<T>::Initialize(const T& start, const T& end, const float exponent)
{
	// ‘ã“ü
	start_ = start;
	end_ = end;
	exponent_ = exponent;
}

template<typename T>
T Ease<T>::In(const float ratio) { return EaseIn<T>(start_, end_, ratio, exponent_); }

template<typename T>
T Ease<T>::Out(const float ratio) { return EaseOut<T>(start_, end_, ratio, exponent_); }

template class Ease<float>;
template class Ease<double>;
template class Ease<Vector2>;
template class Ease<Vector3>;
template class Ease<Vector4>;