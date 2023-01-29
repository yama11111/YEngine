#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include <vector>

namespace YMath
{
	// 補間
	template<typename T>
	T Lerp(const T& a, const T& b, const float t);

	// 3次元補間
	Vec3 Slerp(const Vec3& v1, const Vec3& v2, float t);

	// イーズイン(だんだん早く)
	template<typename T>
	T EaseIn(const T& start, const T& end, const float time, const float power);
	// イーズアウト(だんだん遅く)
	template<typename T>
	T EaseOut(const T& start, const T& end, const float time, const float power);
	// ベジエ曲線
	Vec3 Bezier(const std::vector<Vec3>& points, const float time);
	// スプライン曲線
	Vec3 Spline(const std::vector<Vec3>& points, const size_t section, const float time);
	// ベジエ曲線(イーズイン)
	Vec3 EaseInBezier(const std::vector<Vec3>& points, const float time, const float power);
	// ベジエ曲線(イーズアウト)
	Vec3 EaseOutBezier(const std::vector<Vec3>& points, const float time, const float power);
	//// スプライン曲線(イーズイン)
	//Vec3 EaseInSpline(const std::vector<Vec3>& points, const size_t section, const float time, const float power);
	//// スプライン曲線(イーズアウト)
	//Vec3 EaseOutSpline(const std::vector<Vec3>& points, const size_t section, const float time, const float power);


	// イージングクラス
	template<typename T>
	class Ease
	{
	private:
		// 初期値
		T start_ = T();
		// 最終値
		T end_ = T();
		// 緩急(指数)
		float power_ = 0.0f;
	public:
		// 初期化
		void Initialize(const T& start, const T& end, const float power);
		// イーズイン(だんだん早く)
		T In(const float time);
		// イーズアウト(だんだん遅く)
		T Out(const float time);
	public:
		// 初期値設定
		void SetStart(const T& start) { start_ = start; };
		// 最終値設定 
		void SetEnd(const T& end) { end_ = end; };
		// 緩急設定
		void SetPower(const float power) { power_ = power; }
	};


	// 曲線イージングクラス
	class BezierEase
	{
	private:
		// 値
		std::vector<Vec3> points_{};
		// 緩急(指数)
		float power_ = 0.0f;
	public:
		// 初期化
		void Initialize(const std::vector<Vec3>& points, const float power);
	public:
		// イーズイン(Bezier)
		Vec3 In(const float time);
		// イーズアウト(Bezier)
		Vec3 Out(const float time);
	public:
		// 初期値設定
		void SetStart(const std::vector<Vec3>& points) { points_ = points; };
		// 緩急設定
		void SetPower(const float power) { power_ = power; }
	};
}
