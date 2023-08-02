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
		// �R���X�g���N�^(��x�N�g��)
		Vector4();
		// �R���X�g���N�^(�����L)
		Vector4(float r, float g, float b, float a);
	public:
		// �P�����Z�q
		Vector4 operator+() const;
		Vector4 operator-() const;
		// ������Z�q
		Vector4& operator+=(const Vector4& v);
		Vector4& operator-=(const Vector4& v);
		Vector4& operator*=(float s);
		Vector4& operator/=(float s);
		// ��r���Z�q
		bool operator==(const Vector4& v);
		bool operator!=(const Vector4& v);
	};
	// �񍀉��Z�q
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
