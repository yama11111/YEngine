#pragma once

namespace Math
{
	struct Vec3
	{
	public:
		float x_;
		float y_;
		float z_;
	public:
		// コンストラクタ(零ベクトル)
		Vec3();
		// コンストラクタ(引数有)
		Vec3(float x, float y, float z);
	public:
		// ノルム(長さ)
		float Length() const;
		// 長さ 2乗
		constexpr float LengthSquare() const;
		// 正規化
		Vec3 Normalized() const;
		// 零ベクトルか
		constexpr bool IsZero() const;
		// 内積
		constexpr float Dot(const Vec3& v) const;
		// 外積
		Vec3 Cross(const Vec3& v);
		// 距離
		float Distance(const Vec3& v) const;
	public:
		// 単項演算子
		Vec3 operator+() const;
		Vec3 operator-() const;
		// 代入演算子
		Vec3& operator+=(const Vec3& v);
		Vec3& operator-=(const Vec3& v);
		Vec3& operator*=(float s);
		Vec3& operator/=(float s);
		// 比較演算子
		bool operator==(const Vec3& v);
		bool operator!=(const Vec3& v);
	};
	// 二項演算子
	inline Vec3 operator+(const Vec3& v1, const Vec3& v2)
	{
		return { v1.x_ + v2.x_, v1.y_ + v2.y_, v1.z_ + v2.z_ };
	}
	inline Vec3 operator-(const Vec3& v1, const Vec3& v2)
	{
		return { v1.x_ - v2.x_, v1.y_ - v2.y_, v1.z_ - v2.z_ };
	}
	inline Vec3 operator*(const Vec3& v, float s)
	{
		return { v.x_ * s, v.y_ * s, v.z_ * s };
	}
	inline Vec3 operator*(float s, const Vec3& v)
	{
		return { s * v.x_, s * v.y_, s * v.z_ };
	}
	inline Vec3 operator/(const Vec3& v, float s)
	{
		return { v.x_ / s, v.y_ / s, v.z_ / s };
	}
}