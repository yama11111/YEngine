#pragma once
#include "Vec4.h"

namespace Math
{
	// —”‰Šú‰»
	void Srand();
	// —”æ“¾
	int GetRand(const int start, const int end);

	// •„†
	template<typename T>
	T Sign(const T num);

	// ”ÍˆÍ§ŒÀ
	template<typename T>
	T Clamp(const T num, const T lower, const T upper);

	// F•ÏŠ·((0`255)¨(0.0`1.0))
	Vec4 GetColor(const int R, const int G, const int B, const int A);
}

