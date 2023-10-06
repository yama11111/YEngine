#pragma once

namespace YMath
{
	struct Vector4
	{
	public:
		float r_;
		float g_;
		float b_;
		float a_;
	public:
		// コンストラクタ(零ベクトル)
		Vector4();
		// コンストラクタ(引数有)
		Vector4(float r, float g, float b, float a);
	public:
		// 単項演算子
		Vector4 operator+() const;
		Vector4 operator-() const;
		// 代入演算子
		Vector4& operator+=(const Vector4& v);
		Vector4& operator-=(const Vector4& v);
		Vector4& operator*=(float s);
		Vector4& operator/=(float s);
		// 比較演算子
		bool operator==(const Vector4& v);
		bool operator!=(const Vector4& v);
	};
	// 二項演算子
	inline Vector4 operator+(const Vector4& v1, const Vector4& v2)
	{
		return { v1.r_ + v2.r_, v1.g_ + v2.g_, v1.b_ + v2.b_, v1.a_ + v2.a_ };
	}
	inline Vector4 operator-(const Vector4& v1, const Vector4& v2)
	{
		return { v1.r_ - v2.r_, v1.g_ - v2.g_, v1.b_ - v2.b_, v1.a_ - v2.a_ };
	}
	inline Vector4 operator*(const Vector4& v, float s)
	{
		return { v.r_ * s, v.g_ * s, v.b_ * s, v.a_ * s };
	}
	inline Vector4 operator*(float s, const Vector4& v)
	{
		return { s * v.r_, s * v.g_, s * v.b_, s * v.a_ };
	}
	inline Vector4 operator/(const Vector4& v, float s)
	{
		return { v.r_ / s, v.g_ / s, v.b_ / s, v.a_ / s };
	}

	using Vec4 = Vector4;
}
