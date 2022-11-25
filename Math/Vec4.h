#pragma once

namespace Math
{
	struct Vec4
	{
	public:
		float r_;
		float g_;
		float b_;
		float a_;
	public:
		// コンストラクタ(零ベクトル)
		Vec4();
		// コンストラクタ(引数有)
		Vec4(float r, float g, float b, float a);
	public:
		// 単項演算子
		Vec4 operator+() const;
		Vec4 operator-() const;
		// 代入演算子
		Vec4& operator+=(const Vec4& v);
		Vec4& operator-=(const Vec4& v);
		Vec4& operator*=(float s);
		Vec4& operator/=(float s);
		// 比較演算子
		bool operator==(const Vec4& v);
		bool operator!=(const Vec4& v);
	};
	// 二項演算子
	inline Vec4 operator+(const Vec4& v1, const Vec4& v2)
	{
		return { v1.r_ + v2.r_, v1.g_ + v2.g_, v1.b_ + v2.b_, v1.a_ + v2.a_ };
	}
	inline Vec4 operator-(const Vec4& v1, const Vec4& v2)
	{
		return { v1.r_ - v2.r_, v1.g_ - v2.g_, v1.b_ - v2.b_, v1.a_ - v2.a_ };
	}
	inline Vec4 operator*(const Vec4& v, float s)
	{
		return { v.r_ * s, v.g_ * s, v.b_ * s, v.a_ * s };
	}
	inline Vec4 operator*(float s, const Vec4& v)
	{
		return { s * v.r_, s * v.g_, s * v.b_, s * v.a_ };
	}
	inline Vec4 operator/(const Vec4& v, float s)
	{
		return { v.r_ / s, v.g_ / s, v.b_ / s, v.a_ / s };
	}
}
