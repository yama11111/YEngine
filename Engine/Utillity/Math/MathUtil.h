#pragma once
#include "Vector3.h"
#include "Vector4.h"

namespace YMath
{
	// 乱数初期化
	void Srand();
	
	// 乱数取得
	int GetRand(const int start, const int end);
	float GetRand(const float start, const float end, const float place);
	Vector3 GetRand(const Vector3& start, const Vector3& end, const float place);

	// 符号
	template<typename T>
	T Sign(const T num);
	
	// 範囲内か
	template<typename T>
	bool InRange(const T& num, const T& lower, const T& upper);

	// 範囲制限
	template<typename T>
	T Clamp(const T& num, const T& lower, const T& upper);

	// 色変換((0～255)→(0.0～1.0))
	Vector4 GetColor(const int R, const int G, const int B, const int A);

	// 度数からラジアンに変換
	float ConvertFromDegreeToRadian(const float degree);
	
	Vector3 ConvertFromDegreeToRadian(const Vector3& degree);
}

