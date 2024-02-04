#pragma once

namespace YMath
{
	struct Vector3
	{
	public:
		float x;
		float y;
		float z;
	public:
		// コンストラクタ(零ベクトル)
		Vector3();
		// コンストラクタ(引数有)
		Vector3(float x, float y, float z);
	public:
		// ノルム(長さ)
		float Length() const;
		// 長さ 2乗
		constexpr float LengthSquare() const;
		// 正規化
		Vector3 Normalized() const;
		// 零ベクトルか
		constexpr bool IsZero() const;
		// 内積
		constexpr float Dot(const Vector3& v) const;
		// 外積
		Vector3 Cross(const Vector3& v) const;
		// 距離
		float Distance(const Vector3& v) const;
	public:
		// 単項演算子
		Vector3 operator+() const;
		Vector3 operator-() const;
		// 代入演算子
		Vector3& operator+=(const Vector3& v);
		Vector3& operator-=(const Vector3& v);
		Vector3& operator*=(float s);
		Vector3& operator/=(float s);
		// 比較演算子
		bool operator==(const Vector3& v);
		bool operator!=(const Vector3& v);
	};
	// 二項演算子
	inline Vector3 operator+(const Vector3& v1, const Vector3& v2)
	{
		return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
	}
	inline Vector3 operator-(const Vector3& v1, const Vector3& v2)
	{
		return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
	}
	inline Vector3 operator*(const Vector3& v, float s)
	{
		return { v.x * s, v.y * s, v.z * s };
	}
	inline Vector3 operator*(float s, const Vector3& v)
	{
		return { s * v.x, s * v.y, s * v.z };
	}
	inline Vector3 operator/(const Vector3& v, float s)
	{
		return { v.x / s, v.y / s, v.z / s };
	}

	using Vec3 = Vector3;
}