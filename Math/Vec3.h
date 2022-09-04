#pragma once

namespace Math
{
	struct Vec3
	{
	public:
		float x;
		float y;
		float z;
	public:
		constexpr Vec3(); // 零ベクトル
		constexpr Vec3(const float x, const float y, const float z);

		float Length() const;					// ノルム(長さ)
		constexpr float LengthSquare() const;	// 長さ 2乗
		Vec3 Normalized() const;				// 正規化
		constexpr bool IsZero() const;			// 零ベクトルか

		constexpr float Dot(const Vec3& v) const; // 内積
		Vec3 Cross(const Vec3& v); // 外積
		float Distance(const Vec3& v) const; // 距離
	public:
		// 単項演算子
		constexpr Vec3 operator+() const;
		constexpr Vec3 operator-() const;
		constexpr Vec3 operator+(const Vec3& v) const;
		constexpr Vec3 operator-(const Vec3& v) const;
		constexpr Vec3 operator*(float s) const;
		constexpr Vec3 operator/(float s) const;

		// 代入演算子
		Vec3& operator+=(const Vec3& v);
		Vec3& operator-=(const Vec3& v);
		Vec3& operator*=(float s);
		Vec3& operator/=(float s);
	};

	// 二項演算子
	inline constexpr Vec3 operator *(float s, const Vec3& v);
}