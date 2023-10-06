#include "Lerp.h"
#include "Vector2.h"
#include "Vector4.h"
#include <cmath>
#include <cassert>

using YMath::Vector2;
using YMath::Vector3;
using YMath::Vector4;

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
T YMath::Bezier(const std::vector<T>& points, const float ratio)
{
	// 1つもないなら弾く
	assert(points.empty() == false);

	// 1つなら 0番を返す
	if (points.size() == 1) { return points[0]; }
	
	// 2つなら 普通の補間
	if (points.size() == 2) { return Lerp<T>(points[0], points[1], ratio); }

	// 計算用に宣言
	std::vector<T> p = points, result;
	while (true)
	{
		// 計算用ベクタークリア
		result.clear();
		
		// 現在の基準点の数回す
		for (size_t i = 0; i < p.size() - 1; i++)
		{
			// 計算用ベクターに代入
			result.push_back(Lerp<T>(p[i], p[i + 1], ratio));
		}
		
		// 2つ以下になったら終了
		if (result.size() <= 2) { break; }
		
		// 代入
		p = result;
	}

	// 計算用ベクターで補間
	return Lerp<T>(result[0], result[1], ratio);
}

namespace
{
	void CalcSplineSectionAndRatio(const size_t sectionNum, const float ratio, size_t& section, float& ratioOfSection)
	{
		// 全体での割合 (size : 1.0 = x : ratio)
		float ratioOfTotal = ratio * static_cast<float>(sectionNum);

		// 全体の割合から、セクション と 割合 を計算

		// 割合 : 全体の割合の 少数部
		float integer = 0;
		ratioOfSection = modff(ratioOfTotal, &integer);

		// セクション : 全体の割合の 整数部
		section = static_cast<size_t>(integer);
	}
}

template<typename T>
T YMath::Spline(const std::vector<T>& points, const float ratio)
{
	// 1つもないなら弾く
	assert(points.empty() == false);

	size_t pSize = points.size();

	// 1つなら 0番を返す
	if (pSize == 1) { return points[0]; }

	// 2つなら 普通の補間
	if (pSize == 2) { return Lerp<T>(points[0], points[1], ratio); }

	size_t section = 0;
	float ratioOfSection = 0.0f;
	CalcSplineSectionAndRatio(pSize - 1, ratio, section, ratioOfSection);

	// セクションが 配列の最大数を超えているなら 最後を返す
	// セクションが 負の値なら 最初を返す
	size_t max = pSize - 2;
	if (section > max) { return points[pSize - 1]; }
	if (section < 0) { return points[0]; }

	// 必ず4点以上でなければならないので、
	// 新規に宣言し、最初と最後を複製
	std::vector<T> ps;
	ps.emplace_back(points[0]);
	for (size_t i = 0; i < pSize; i++)
	{
		ps.emplace_back(points[i]);
	}
	ps.emplace_back(points[pSize - 1]);

	// 計算
	T p0 = ps[section];
	T p1 = ps[section + 1];
	T p2 = ps[section + 2];
	T p3 = ps[section + 3];

	T position =
		0.5f * ((2 * p1) + (-p0 + p2) * ratioOfSection
			+ ((2 * p0) - (5 * p1) + (4 * p2) - p3) * powf(ratioOfSection, 2.0f)
			+ (-p0 + (3 * p1) - (3 * p2) + p3) * powf(ratioOfSection, 3.0f));

	return position;
}

namespace 
{
	float EaseInRatio(const float ratio, const float exponent)
	{
		return powf(ratio, exponent);
	}
	
	float EaseOutRatio(const float ratio, const float exponent)
	{
		return 1.0f - powf(1.0f - ratio, exponent);
	}

	float EaseInOutRatio(const float ratio, const float exponent, const float controlPoint)
	{
		// グラフを分割しないなら 先に値を返す
		// (0除算を無くす意味もある)
		
		if (1.0f <= controlPoint) { return EaseInRatio(ratio, exponent); }
		if (controlPoint <= 0.0f) { return EaseOutRatio(ratio, exponent); }

		// (1) 制御点 から グラフを分割
		// (2) それぞれの グラフにおいての割合 を再計算
		// (3) その割合 を 元のグラフでの値 に戻す
		
		// (1)
		if (ratio <= controlPoint)
		{
			float rocalRatio = ratio / controlPoint; // (2)
			return YMath::Lerp(0.0f, controlPoint, EaseInRatio(rocalRatio, exponent)); // (3)
		}
		else
		{
			float rocalRatio = (ratio - controlPoint) / (1.0f - controlPoint); // (2)
			return YMath::Lerp(controlPoint, 1.0f, EaseOutRatio(rocalRatio, exponent)); // (3)
		}
	}
	
	float EaseOutInRatio(const float ratio, const float exponent, const float controlPoint)
	{
		// グラフを分割しないなら 先に値を返す
		// (0除算を無くす意味もある)
		
		if (1.0f <= controlPoint) { return EaseOutRatio(ratio, exponent); }
		if (controlPoint <= 0.0f) { return EaseInRatio(ratio, exponent); }

		// (1) 制御点 から グラフを分割
		// (2) それぞれの グラフにおいての割合 を再計算
		// (3) その割合 を 元のグラフでの値 に戻す
		
		// (1)
		if (ratio <= controlPoint)
		{
			float rocalRatio = ratio / controlPoint; // (2)
			return YMath::Lerp(0.0f, controlPoint, EaseOutRatio(rocalRatio, exponent)); // (3)
		}
		else
		{
			float rocalRatio = (ratio - controlPoint) / (1.0f - controlPoint); // (2)
			return YMath::Lerp(controlPoint, 1.0f, EaseInRatio(rocalRatio, exponent)); // (3)
		}
	}
}

#pragma region Ease

template<typename T>
T YMath::EaseIn(const T& start, const T& end, const float ratio, const float exponent)
{
	return Lerp<T>(start, end, EaseInRatio(ratio, exponent));
}
template<typename T>
T YMath::EaseOut(const T& start, const T& end, const float ratio, const float exponent)
{
	return Lerp<T>(start, end, EaseOutRatio(ratio, exponent));
}
template<typename T>
T YMath::EaseInOut(const T& start, const T& end, const float ratio, const float exponent, const float controlPoint)
{
	return Lerp<T>(start, end, EaseInOutRatio(ratio, exponent, controlPoint));
}
template<typename T>
T YMath::EaseOutIn(const T& start, const T& end, const float ratio, const float exponent, const float controlPoint)
{
	return Lerp<T>(start, end, EaseOutInRatio(ratio, exponent, controlPoint));
}

#pragma endregion

#pragma region BezierEase

template<typename T>
T YMath::BezierEaseIn(const std::vector<T>& points, const float ratio, const float exponent)
{
	return Bezier<T>(points, EaseInRatio(ratio, exponent));
}
template<typename T>
T YMath::BezierEaseOut(const std::vector<T>& points, const float ratio, const float exponent)
{
	return Bezier<T>(points, EaseOutRatio(ratio, exponent));
}
template<typename T>
T YMath::BezierEaseInOut(const std::vector<T>& points, const float ratio, const float exponent, const float controlPoint)
{
	return Bezier<T>(points, EaseInOutRatio(ratio, exponent, controlPoint));
}
template<typename T>
T YMath::BezierEaseOutIn(const std::vector<T>& points, const float ratio, const float exponent, const float controlPoint)
{
	return Bezier<T>(points, EaseOutInRatio(ratio, exponent, controlPoint));
}

#pragma endregion

#pragma region SplineEase

template<typename T>
T YMath::SplineEaseIn(const std::vector<T>& points, const float ratio, const float exponent)
{
	return Spline<T>(points, EaseInRatio(ratio, exponent));
}
template<typename T>
T YMath::SplineEaseOut(const std::vector<T>& points, const float ratio, const float exponent)
{
	return Spline<T>(points, EaseOutRatio(ratio, exponent));
}
template<typename T>
T YMath::SplineEaseInOut(const std::vector<T>& points, const float ratio, const float exponent, const float controlPoint)
{
	return Spline<T>(points, EaseInOutRatio(ratio, exponent, controlPoint));
}
template<typename T>
T YMath::SplineEaseOutIn(const std::vector<T>& points, const float ratio, const float exponent, const float controlPoint)
{
	return Spline<T>(points, EaseOutInRatio(ratio, exponent, controlPoint));
}

#pragma endregion

template float YMath::Lerp<float>(const float& a, const float& b, const float t);
template double YMath::Lerp<double>(const double& a, const double& b, const float t);
template Vector2 YMath::Lerp<Vector2>(const Vector2& a, const Vector2& b, const float t);
template Vector3 YMath::Lerp<Vector3>(const Vector3& a, const Vector3& b, const float t);
template Vector4 YMath::Lerp<Vector4>(const Vector4& a, const Vector4& b, const float t);

template float YMath::Bezier<float>(const std::vector<float>& points, const float t);
template double YMath::Bezier<double>(const std::vector<double>& points, const float t);
template Vector2 YMath::Bezier<Vector2>(const std::vector<Vector2>& points, const float t);
template Vector3 YMath::Bezier<Vector3>(const std::vector<Vector3>& points, const float t);
template Vector4 YMath::Bezier<Vector4>(const std::vector<Vector4>& points, const float t);

template float YMath::Spline<float>(const std::vector<float>& points, const float ratio);
template double YMath::Spline<double>(const std::vector<double>& points, const float ratio);
template Vector2 YMath::Spline<Vector2>(const std::vector<Vector2>& points, const float ratio);
template Vector3 YMath::Spline<Vector3>(const std::vector<Vector3>& points, const float ratio);
template Vector4 YMath::Spline<Vector4>(const std::vector<Vector4>& points, const float ratio);


template float YMath::EaseIn<float>(const float& start, const float& end, const float ratio, const float exponent);
template double YMath::EaseIn<double>(const double& start, const double& end, const float ratio, const float exponent);
template Vector2 YMath::EaseIn<Vector2>(const Vector2& start, const Vector2& end, const float ratio, const float exponent);
template Vector3 YMath::EaseIn<Vector3>(const Vector3& start, const Vector3& end, const float ratio, const float exponent);
template Vector4 YMath::EaseIn<Vector4>(const Vector4& start, const Vector4& end, const float ratio, const float exponent);

template float YMath::EaseOut<float>(const float& start, const float& end, const float ratio, const float exponent);
template double YMath::EaseOut<double>(const double& start, const double& end, const float ratio, const float exponent);
template Vector2 YMath::EaseOut<Vector2>(const Vector2& start, const Vector2& end, const float ratio, const float exponent);
template Vector3 YMath::EaseOut<Vector3>(const Vector3& start, const Vector3& end, const float ratio, const float exponent);
template Vector4 YMath::EaseOut<Vector4>(const Vector4& start, const Vector4& end, const float ratio, const float exponent);

template float YMath::EaseInOut<float>(const float& start, const float& end, const float ratio, const float exponent, const float controlPoint);
template double YMath::EaseInOut<double>(const double& start, const double& end, const float ratio, const float exponent, const float controlPoint);
template Vector2 YMath::EaseInOut<Vector2>(const Vector2& start, const Vector2& end, const float ratio, const float exponent, const float controlPoint);
template Vector3 YMath::EaseInOut<Vector3>(const Vector3& start, const Vector3& end, const float ratio, const float exponent, const float controlPoint);
template Vector4 YMath::EaseInOut<Vector4>(const Vector4& start, const Vector4& end, const float ratio, const float exponent, const float controlPoint);

template float YMath::EaseOutIn<float>(const float& start, const float& end, const float ratio, const float exponent, const float controlPoint);
template double YMath::EaseOutIn<double>(const double& start, const double& end, const float ratio, const float exponent, const float controlPoint);
template Vector2 YMath::EaseOutIn<Vector2>(const Vector2& start, const Vector2& end, const float ratio, const float exponent, const float controlPoint);
template Vector3 YMath::EaseOutIn<Vector3>(const Vector3& start, const Vector3& end, const float ratio, const float exponent, const float controlPoint);
template Vector4 YMath::EaseOutIn<Vector4>(const Vector4& start, const Vector4& end, const float ratio, const float exponent, const float controlPoint);


template float YMath::BezierEaseIn<float>(const std::vector<float>& points, const float ratio, const float exponent);
template double YMath::BezierEaseIn<double>(const std::vector<double>& points, const float ratio, const float exponent);
template Vector2 YMath::BezierEaseIn<Vector2>(const std::vector<Vector2>& points, const float ratio, const float exponent);
template Vector3 YMath::BezierEaseIn<Vector3>(const std::vector<Vector3>& points, const float ratio, const float exponent);
template Vector4 YMath::BezierEaseIn<Vector4>(const std::vector<Vector4>& points, const float ratio, const float exponent);

template float YMath::BezierEaseOut<float>(const std::vector<float>& points, const float ratio, const float exponent);
template double YMath::BezierEaseOut<double>(const std::vector<double>& points, const float ratio, const float exponent);
template Vector2 YMath::BezierEaseOut<Vector2>(const std::vector<Vector2>& points, const float ratio, const float exponent);
template Vector3 YMath::BezierEaseOut<Vector3>(const std::vector<Vector3>& points, const float ratio, const float exponent);
template Vector4 YMath::BezierEaseOut<Vector4>(const std::vector<Vector4>& points, const float ratio, const float exponent);

template float YMath::BezierEaseInOut<float>(const std::vector<float>& points, const float ratio, const float exponent, const float controlPoint);
template double YMath::BezierEaseInOut<double>(const std::vector<double>& points, const float ratio, const float exponent, const float controlPoint);
template Vector2 YMath::BezierEaseInOut<Vector2>(const std::vector<Vector2>& points, const float ratio, const float exponent, const float controlPoint);
template Vector3 YMath::BezierEaseInOut<Vector3>(const std::vector<Vector3>& points, const float ratio, const float exponent, const float controlPoint);
template Vector4 YMath::BezierEaseInOut<Vector4>(const std::vector<Vector4>& points, const float ratio, const float exponent, const float controlPoint);

template float YMath::BezierEaseOutIn<float>(const std::vector<float>& points, const float ratio, const float exponent, const float controlPoint);
template double YMath::BezierEaseOutIn<double>(const std::vector<double>& points, const float ratio, const float exponent, const float controlPoint);
template Vector2 YMath::BezierEaseOutIn<Vector2>(const std::vector<Vector2>& points, const float ratio, const float exponent, const float controlPoint);
template Vector3 YMath::BezierEaseOutIn<Vector3>(const std::vector<Vector3>& points, const float ratio, const float exponent, const float controlPoint);
template Vector4 YMath::BezierEaseOutIn<Vector4>(const std::vector<Vector4>& points, const float ratio, const float exponent, const float controlPoint);


template float YMath::SplineEaseIn<float>(const std::vector<float>& points, const float ratio, const float exponent);
template double YMath::SplineEaseIn<double>(const std::vector<double>& points, const float ratio, const float exponent);
template Vector2 YMath::SplineEaseIn<Vector2>(const std::vector<Vector2>& points, const float ratio, const float exponent);
template Vector3 YMath::SplineEaseIn<Vector3>(const std::vector<Vector3>& points, const float ratio, const float exponent);
template Vector4 YMath::SplineEaseIn<Vector4>(const std::vector<Vector4>& points, const float ratio, const float exponent);

template float YMath::SplineEaseOut<float>(const std::vector<float>& points, const float ratio, const float exponent);
template double YMath::SplineEaseOut<double>(const std::vector<double>& points, const float ratio, const float exponent);
template Vector2 YMath::SplineEaseOut<Vector2>(const std::vector<Vector2>& points, const float ratio, const float exponent);
template Vector3 YMath::SplineEaseOut<Vector3>(const std::vector<Vector3>& points, const float ratio, const float exponent);
template Vector4 YMath::SplineEaseOut<Vector4>(const std::vector<Vector4>& points, const float ratio, const float exponent);

template float YMath::SplineEaseInOut<float>(const std::vector<float>& points, const float ratio, const float exponent, const float controlPoint);
template double YMath::SplineEaseInOut<double>(const std::vector<double>& points, const float ratio, const float exponent, const float controlPoint);
template Vector2 YMath::SplineEaseInOut<Vector2>(const std::vector<Vector2>& points, const float ratio, const float exponent, const float controlPoint);
template Vector3 YMath::SplineEaseInOut<Vector3>(const std::vector<Vector3>& points, const float ratio, const float exponent, const float controlPoint);
template Vector4 YMath::SplineEaseInOut<Vector4>(const std::vector<Vector4>& points, const float ratio, const float exponent, const float controlPoint);

template float YMath::SplineEaseOutIn<float>(const std::vector<float>& points, const float ratio, const float exponent, const float controlPoint);
template double YMath::SplineEaseOutIn<double>(const std::vector<double>& points, const float ratio, const float exponent, const float controlPoint);
template Vector2 YMath::SplineEaseOutIn<Vector2>(const std::vector<Vector2>& points, const float ratio, const float exponent, const float controlPoint);
template Vector3 YMath::SplineEaseOutIn<Vector3>(const std::vector<Vector3>& points, const float ratio, const float exponent, const float controlPoint);
template Vector4 YMath::SplineEaseOutIn<Vector4>(const std::vector<Vector4>& points, const float ratio, const float exponent, const float controlPoint);