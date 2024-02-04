#pragma once

namespace YMath
{
	struct Vector4
	{
	public:
		float x;
		float y;
		float z;
		float w;
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
		return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w };
	}
	inline Vector4 operator-(const Vector4& v1, const Vector4& v2)
	{
		return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w };
	}
	inline Vector4 operator*(const Vector4& v, float s)
	{
		return { v.x * s, v.y * s, v.z * s, v.w * s };
	}
	inline Vector4 operator*(float s, const Vector4& v)
	{
		return { s * v.x, s * v.y, s * v.z, s * v.w };
	}
	inline Vector4 operator/(const Vector4& v, float s)
	{
		return { v.x / s, v.y / s, v.z / s, v.w / s };
	}

	using Vec4 = Vector4;
}
