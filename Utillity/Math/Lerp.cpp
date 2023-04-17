#include "Lerp.h"
#include "Vector4.h"
#include <math.h>
#include <cassert>

using YMath::Ease;
using YMath::BezierEase;
using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;

#pragma region 補間

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

#pragma endregion 


#pragma region イージング

template<typename T>
T YMath::EaseIn(const T& start, const T& end, const float ratio, const float exponent)
{
	return Lerp<T>(start, end, powf(ratio, exponent));
}
template<typename T>
T YMath::EaseOut(const T& start, const T& end, const float ratio, const float exponent)
{
	return Lerp<T>(start, end, 1 - powf(1 - ratio, exponent));
}

Vector3 YMath::Bezier(const std::vector<Vector3>& points, const float ratio)
{
	// 1つもないなら弾く
	assert(!points.empty());

	// 1つなら 0番を返す
	if (points.size() == 1) { return points[0]; }
	
	// 2つなら 普通の補間
	if (points.size() == 2) { return Lerp(points[0], points[1], ratio); }

	// 計算用に宣言
	std::vector<Vector3> p = points, result;
	while (true)
	{
		// 計算用ベクタークリア
		result.clear();
		
		// 現在の基準点の数回す
		for (size_t i = 0; i < p.size() - 1; i++)
		{
			// 計算用ベクターに代入
			result.push_back(Lerp(p[i], p[i + 1], ratio));
		}
		
		// 2つ以下になったら終了
		if (result.size() <= 2) { break; }
		
		// 代入
		p = result;
	}

	// 計算用ベクターで補間
	return Lerp(result[0], result[1], ratio);
}
Vector3 YMath::Spline(const std::vector<Vector3>& points, const size_t section, const float ratio)
{
	// 4つ未満なら弾く
	assert(4 <= points.size());

	// セクションがベクターの最大数、最小数を超えているならその値返す
	size_t n = points.size() - 4;
	if (section > n) { return points[n]; }
	if (section < 0) { return points[1]; }

	// 計算
	Vector3 p0 = points[section];
	Vector3 p1 = points[section + 1];
	Vector3 p2 = points[section + 2];
	Vector3 p3 = points[section + 3];

	Vector3 position =
		0.5f * ((2 * p1) + (-p0 + p2) * ratio
			+ ((2 * p0) - (5 * p1) + (4 * p2) - p3) * powf(ratio, 2.0f)
			+ (-p0 + (3 * p1) - (3 * p2) + p3) * powf(ratio, 3.0f));

	return position;
}

Vector3 YMath::EaseInBezier(const std::vector<Vector3>& points, const float ratio, const float exponent)
{
	return Bezier(points, powf(ratio, exponent));
}
Vector3 YMath::EaseOutBezier(const std::vector<Vector3>& points, const float ratio, const float exponent)
{
	return Bezier(points, 1 - powf(1 - ratio, exponent));
}

#pragma endregion 


#pragma region Ease クラス

template<typename T>
void Ease<T>::Initialize(const T& start, const T& end, const float exponent)
{
	// 代入
	start_ = start;
	end_ = end;
	exponent_ = exponent;
}

template<typename T>
T Ease<T>::In(const float ratio) { return EaseIn<T>(start_, end_, ratio, exponent_); }

template<typename T>
T Ease<T>::Out(const float ratio) { return EaseOut<T>(start_, end_, ratio, exponent_); }

template class Ease<int>;
template class Ease<float>;
template class Ease<double>;
template class Ease<Vector2>;
template class Ease<Vector3>;
template class Ease<Vector4>;

#pragma endregion 


#pragma region BezierEase クラス

void BezierEase::Initialize(const std::vector<Vector3>& points, const float exponent)
{
	// 1つもないなら弾く
	assert(!points.empty());

	// 代入
	points_ = points;
	exponent_ = exponent;
}

Vector3 BezierEase::In(const float ratio)
{
	return EaseInBezier(points_, ratio, exponent_);
}
Vector3 BezierEase::Out(const float ratio)
{
	return EaseOutBezier(points_, ratio, exponent_);
}

#pragma endregion 
