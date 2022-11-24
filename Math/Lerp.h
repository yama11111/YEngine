#pragma once
#include "Vec2.h"
#include "Vec3.h"

namespace Math
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
}
